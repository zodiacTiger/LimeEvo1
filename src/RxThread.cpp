//
// Created by ZodiacTiger on 2/7/20.
//


#include <lime/LimeSuite.h>
#include <iostream>
#include <QString>
#include <mutex>
#include "RxThread.hpp"
#include "helpers.hpp"
#include "LimeRadio.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <complex>

Rx::RxThread::RxThread(double freq, bool rxToFile)
  {
    center_freq=freq;
  };

Rx::RxThread::RxThread (QMutex *mu, double freq, unsigned int gain, double sampRate, const double streamRate, size_t rxChannel, size_t rxAntenna, bool rxToFile)
{
 mutex=mu;
 center_freq = freq;
 rx_gain = gain;
 samp_rate = sampRate;
 stream_rate = streamRate;
 channel = rxChannel;
 antenna = rxAntenna;
 rx_to_file = rxToFile;
}

Rx::RxThread::RxThread (double freq, unsigned int gain, double sampRate, const double streamRate, bool rxToFile)
{
  center_freq = freq;
  rx_gain = gain;
  samp_rate = sampRate;
  stream_rate = streamRate;
}

Rx::RxThread::~RxThread ()
  {
    delete this;
  };

void Rx::RxThread::stop()
{
  bStopped=true;
}

void Rx::RxThread::run()
{
  this->setPriority (HighestPriority);
  mutex->lock ();
  auto startTime = std::chrono::high_resolution_clock::now ();
  auto timeLimit = std::chrono::high_resolution_clock::now ();
  auto timeLastStatus = std::chrono::high_resolution_clock::now ();
  struct iq_buff{
    float i;
    float q;
  };
if(rx_to_file)
  {
  std::string str_output_filename = RX_OUTPUT_FILENAME;
    std::vector<char> output_filename(str_output_filename.c_str(), str_output_filename.c_str() + str_output_filename.size() + 1u);
    if ( !output_filename.empty() ) {
      fd = fopen( &output_filename[0], "w+b" );
      if ( fd == NULL ) {
        perror("fopen()");
        qDebug()<<"ERROR: File Open error";
        }
      } else {
      stdout = stderr;
      }
  }
  lms_info_str_t devInfo[8];
  LMS_GetDeviceList (devInfo);

  if(LMS_Open (&lime_device,devInfo[0], nullptr) != 0)
    {
      qDebug() << "\n[LIME DEVICE] Unable to open device.\n";
    }
    else{

    LMS_Init (lime_device);
    qDebug() << "[LIME DEVICE] Initialized.";

    LMS_EnableChannel (lime_device,LMS_CH_RX,channel,true);
    qDebug() << "[LIME DEVICE] Rx Channel " << "0" << " Enabled";

    LMS_SetSampleRate (lime_device,samp_rate,2);
    qDebug() << "[LIME DEVICE] Sample rate set at " << samp_rate << " Ms/s";

    LMS_SetLOFrequency (lime_device,LMS_CH_RX,channel,center_freq);
    qDebug() << "[LIME DEVICE] Freq set at " << center_freq << " Hz";

    LMS_SetAntenna (lime_device,LMS_CH_RX,channel,LMS_PATH_LNAW);
    qDebug() << "[LIME DEVICE] Antenna set at -> " << antenna << "";

    LMS_SetLPFBW (lime_device,LMS_CH_RX,channel,bw);
    qDebug() << "[LIME DEVICE] LPF set at " << bw << " Hz";

    LMS_SetNormalizedGain (lime_device,LMS_CH_RX,channel,0);
    qDebug() << "[LIME DEVICE] Normalized Gain set at " << "0" << " db";

    LMS_SetGaindB (lime_device,LMS_CH_RX,channel,rx_gain);
    qDebug() << "[LIME DEVICE] Gain set at " << rx_gain << " db";

    LMS_Calibrate (lime_device,LMS_CH_RX,channel,bw,0);
    qDebug() << "[LIME DEVICE] Calibrating for " << samp_rate << " Ms/s";

    // test signal
    LMS_SetTestSignal(lime_device, LMS_CH_RX, 0, LMS_TESTSIG_NONE, 0, 0);

    bStopped = false;
    totalSamples = 0;


//    float *buffer[bufferSize * 2];
//    float buffer[bufferSize*2];

//    void *samps[] = {buffer};
//    std::complex<float> num = *buffer;
//    std::vector<float *>buffer[bufferSize * 2];

    rx_stream.channel = channel;
    rx_stream.fifoSize = fifo_size;
    rx_stream.throughputVsLatency=stream_rate;
    rx_stream.isTx = false;
    rx_stream.dataFmt = lms_stream_t::LMS_FMT_F32;
    rx_meta.waitForTimestamp = false;
    rx_meta.flushPartialPacket = false;

    LMS_SetupStream (lime_device,&rx_stream);
    std::cout << "[INFO] Stream Configured";
    LMS_StartStream (&rx_stream);
    std::cout << "\n[INFO] Stream Running!";
    bStreamActive = true;
    startTime = std::chrono::high_resolution_clock::now();

    while(bStreamActive)
      {
      int samples=LMS_RecvStream (&rx_stream,&buffer,bufferSize,&rx_meta,3000);
      totalSamples = totalSamples + samples;
      tempRXSamp = *buffer;
      if(rx_to_file)
        {
          fwrite( buffer, sizeof(samples), bufferSize*2, fd );
          fflush( fd );
        }
//      for(int i=0;i<samples;i++)
//        {
//          qDebug()<<"i="<<buffer[2 * i] <<",q="<<buffer[2*i+1];
//        }
      const auto now=std::chrono::high_resolution_clock::now ();

      LMS_GetStreamStatus (&rx_stream,&stream_status);

      if(stream_status.droppedPackets > 0)
        {
        qDebug() << "[WARNING] Dropped packets.";
        droppedPackets++;
        }
      if(stream_status.overrun > 0)
        {
          qDebug() << "[WARNING] Overrun detected.";
          overruns++;
        }
      if(stream_status.underrun > 0)
        {
        qDebug() << "[WARNING] Underrun detected.";
        underruns++;
        }

      const auto timePassed = std::chrono::duration_cast<std::chrono::microseconds>(now - startTime);
      if(timeLastStatus + std::chrono::milliseconds(500) < now)
        {
        timeLastStatus = now;
        data_rate = double(totalSamples)/timePassed.count();
        qDebug()<<"[ts]="<<stream_status.timestamp;
        }
      }
    if(rx_to_file)
      {
        fclose(fd);
      }
    LMS_StopStream (&rx_stream);
    LMS_DestroyStream (lime_device,&rx_stream);
    LMS_Close (lime_device);
    bStreamActive = false;
    }
    mutex->unlock ();
}

QString Rx::RxThread::getDataRate()
{
  return QString::number(data_rate) + " Ms/S";
}

QString Rx::RxThread::getSampleRate ()
{
  return QString::number (samp_rate) + " Ms";
}

lms_stream_status_t Rx::RxThread::getStreamStatus()
{
  return stream_status;
}

void Rx::RxThread::setRXToFile(bool rxToFile)
{
  rx_to_file = rxToFile;
}

QString Rx::RxThread::getFreq ()
{
  return QString (QString::number(center_freq));
}

QString Rx::RxThread::getCurrentGain ()
{
  if(lime_device != nullptr)
    {
    unsigned int *currentGain = nullptr;
    LMS_GetGaindB (lime_device,false,0,currentGain);
    return QString::number (*currentGain);
    }
    else{
    return QString::number (rx_gain);
    }
}



QString Rx::RxThread::setFreq (double freq, size_t channel, size_t path)
{
  center_freq = freq;
  if(bStreamActive)
    {
    if (LMS_SetLOFrequency (lime_device, path, channel, freq) != 0)
      {
        return "Error: Unable to set frequency @ " + QString::number (freq);
      }
    else
      {
      return "Frequency set at " + QString::number (center_freq) + " Hz";
      }
    }
    else{
    return "[INFO] Configured at " + QString::number (center_freq) + " Hz. Start stream now.";
    }
}

QString Rx::RxThread::setGain(unsigned int gain, size_t channel)
{

  if(bStreamActive)
    {
    if(lime_device != nullptr)
      {
        LMS_SetGaindB (lime_device,false,0,gain);
        return "RX Gain set at " + QString::number (gain) + " db";
      }
    else if(lime_device == nullptr){
        return "[ERROR] Cannot set gain at " + QString::number (gain) + " db";
      }
    }
    else{
      return "[INFO] No Stream in progress.  Gain will be set at " + QString::number (gain) + " db for future device.";
    }
    return "";
}

QString Rx::RxThread::setAntenna(size_t chan, int antenna_index)
{
  QString antenna_name = "-";
  if(bStreamActive)
    {
    switch (antenna_index)
      {
      case 0:
        {
        antenna = LMS_PATH_LNAH;
        antenna_name = "LNAH";
        qDebug () << "LNAH";
        break;
        }
      case 1:
        {
        antenna = LMS_PATH_LNAL;
        antenna_name = "LNAL";
        qDebug () << "LNAL";
        break;
        }
      case 2:
        {
        antenna = LMS_PATH_LNAW;
        antenna_name = "LNAW";
        qDebug () << "LNAW";
        break;
        }
      default:
        {
        antenna = LMS_PATH_LNAW;
        antenna_name = "LNAW";
        qDebug () << "LNAH";
        break;
        }
      }
    LMS_SetAntenna (lime_device, LMS_CH_RX, chan, antenna);
    }
    else{
    switch (antenna_index)
      {
      case 0:
        {
        antenna = LMS_PATH_LNAH;
        antenna_name = "LNAH";
        qDebug () << "LNAH";
        break;
        }
      case 1:
        {
        antenna = LMS_PATH_LNAL;
        antenna_name = "LNAL";
        qDebug () << "LNAL";
        break;
        }
      case 2:
        {
        antenna = LMS_PATH_LNAW;
        antenna_name = "LNAW";
        qDebug () << "LNAW";
        break;
        }
      default:
        {
        antenna = LMS_PATH_LNAW;
        antenna_name = "LNAW";
        qDebug () << "LNAH";
        break;
        }
      }
  }
    return antenna_name;
}

QString Rx::RxThread::setAntennaStreaming(size_t chan, int antenna_index)
{
  QString antenna_name = "-";

    switch(antenna_index)
      {
      case 0:{antenna = LMS_PATH_LNAH; antenna_name="LNAH"; qDebug()<< "LNAH";break;}
      case 1:{antenna = LMS_PATH_LNAL; antenna_name="LNAL"; qDebug()<< "LNAL";break;}
      case 2:{antenna = LMS_PATH_LNAW; antenna_name="LNAW"; qDebug()<< "LNAW";break;}
      default:{antenna = LMS_PATH_LNAW; antenna_name="LNAW"; qDebug()<< "LNAH";break;}
      }
    LMS_SetAntenna (lime_device,LMS_CH_RX,chan,antenna);
    return antenna_name;
}


QString Rx::RxThread::getOverruns()
{
  return QString::number(overruns);
}

QString Rx::RxThread::getTotalSamples()
{
return QString::number (stream_status.fifoFilledCount);
}

QString Rx::RxThread::getDroppedPackets()
{
  return QString::number(droppedPackets);
}

void Rx::RxThread::disableStream ()
{
  bStreamActive = false;
  qDebug()<<">>> Rx stream disabled.";
}
QString Rx::RxThread::getRXSample ()
{
  return "[TimeStamp]="+QString::number (stream_status.timestamp) + "  Imag=" + QString::number (tempRXSamp.imag ()) + " , Real=" + QString::number (tempRXSamp.real ());
}
std::complex<float> Rx::RxThread::getRXSampleComplex ()
{
  return tempRXSamp;
}
int Rx::RxThread::setStreamLatency (double rate)
{
  stream_rate = rate;
  return 0;
}
int Rx::RxThread::setSampleRate (double sampleRate)
{
  samp_rate = sampleRate;
  if(bStreamActive)
    {
      LMS_StopStream (&rx_stream);
      LMS_SetSampleRate (lime_device,sampleRate,2);
      LMS_StartStream (&rx_stream);
    }
  return 0;
}
int Rx::RxThread::setRegister (int address,int value)
{
  return 0;
}
