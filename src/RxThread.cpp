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
#include <LimeDevice.h>

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
    qDebug()<<"\n>> Destructor Called\n\n";
    LMS_EnableChannel (lime_device,LMS_CH_RX,0,false);
    LMS_EnableChannel (lime_device,LMS_CH_TX,0, false);
    LMS_Close (lime_device);
    delete this;
  };

void Rx::RxThread::stop()
{
  QMutexLocker locker1(mutex);
  LMS_StopStream (&rx_stream);
  LMS_DestroyStream (lime_device,&rx_stream);
  LMS_EnableChannel (lime_device,LMS_CH_RX,0,false);
  LMS_EnableChannel (lime_device,LMS_CH_TX,0, false);
    LMS_Reset (lime_device);
  LMS_Close (lime_device);
  bStreamActive = false;
}

void Rx::RxThread::run()
{
  QMutexLocker locker(mutex);
  auto timeLastStatus = std::chrono::high_resolution_clock::now ();
  droppedPackets = 0;
  overruns = 0;
  underruns = 0;
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

//    LMS_SetNormalizedGain (lime_device,LMS_CH_RX,channel,.6);
//    qDebug() << "[LIME DEVICE] Normalized Gain set at " << "0" << " db";

    int ret = LMS_WriteParam(lime_device,LMS7param(G_LNA_RFE),rx_lna_gain);
    qDebug() << "[LIME DEVICE] LNA set at " << rx_lna_gain ;

    ret = LMS_WriteParam(lime_device,LMS7param(G_PGA_RBB),rx_pga_gain);
    qDebug() << "[LIME DEVICE] PGA set at " << rx_pga_gain ;

    ret = LMS_WriteParam(lime_device,LMS7param(G_TIA_RFE),rx_tia_gain);
    qDebug() << "[LIME DEVICE] TIA set at " << rx_tia_gain ;

    LMS_SetGaindB (lime_device,LMS_CH_RX,channel,rx_gain);
    qDebug() << "[LIME DEVICE] Gain set at " << rx_gain << " db";

    LMS_Calibrate (lime_device,LMS_CH_RX,channel,bw,0);
    qDebug() << "[LIME DEVICE] Calibrating for " << samp_rate << " Ms/s";

    // test signal
    LMS_SetTestSignal(lime_device, LMS_CH_RX, 0, LMS_TESTSIG_NONE, 0, 0);
    totalSamples = 0;

//    float *buffer[bufferSize * 2];
//    float buffer[bufferSize*2];
//    void *samps[] = {buffer};
//    std::complex<float> num = *buffer;
//    std::vector<float *>buffer[bufferSize * 2];

    rx_stream.channel = channel;
    rx_stream.fifoSize = fifo_size;
    rx_stream.throughputVsLatency = stream_rate;
    rx_stream.isTx = false;

    LMS_SetupStream (lime_device,&rx_stream);
    std::cout << "[INFO] Stream Configured";
    LMS_StartStream (&rx_stream);
    std::cout << "\n[INFO] Stream Running!";
    bStreamActive = true;
    int i = 0;

    while(bStreamActive)
      {
      auto startTime = std::chrono::high_resolution_clock::now ();
      samples=LMS_RecvStream (&rx_stream,&buffer_f32,bufferSize,&rx_meta,2000);
      totalSamples = totalSamples + samples;
      tempRXSamp = *buffer_f32;
      if(rx_to_file)
        {
        fwrite( buffer_f32, sizeof(samples), bufferSize*2, fd );
        fflush( fd );
        }
//      if(rx_stream.dataFmt == lms_stream_t::LMS_FMT_F32)
//        {
//        samples=LMS_RecvStream (&rx_stream,&buffer_f32,bufferSize,&rx_meta,2000);
//        totalSamples = totalSamples + samples;
//        tempRXSamp = *buffer_f32;
//        if(rx_to_file)
//          {
//          fwrite( buffer_f32, sizeof(samples), bufferSize*2, fd );
//          fflush( fd );
//          }
//        }
//        else if(rx_stream.dataFmt == lms_stream_t::LMS_FMT_I16){
//        samples=LMS_RecvStream (&rx_stream,&buffer_i16,bufferSize,&rx_meta,2000);
//        totalSamples = totalSamples + samples;
//        tempRXSamp = *buffer_i16;
//        if(rx_to_file)
//          {
//          fwrite( buffer_i16, sizeof(samples), bufferSize*2, fd );
//          fflush( fd );
//          }
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

          auto timePassed = std::chrono::duration_cast<std::chrono::microseconds> (now - startTime);
          if (timeLastStatus + std::chrono::milliseconds (1000) < now)
            {
            if (double (totalSamples) / timePassed.count () * 1e6 > samp_rate)
              {
                data_rate = samp_rate;
              }
            else
              {
                data_rate = double (totalSamples) / timePassed.count ();
                timeLastStatus = now;
              }
            }
            i++;
      if(i==samp_rate/UPDATE_RATE_FAST && !plotUpdateTimed)
        {
          emit update_constellation_plot_signal ();
          i = 0;
        }
      totalSamples = 0;
    }
    if(rx_to_file)
      {
        fclose(fd);
      }

    }
}

QString Rx::RxThread::getDataRate()
{
  return QString::number(data_rate) + " Ms/S";
}

QString Rx::RxThread::getSampleRate ()
{
  return QString::number ((int)samp_rate) + " Ms/S";
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

QString Rx::RxThread::getLinkRate()
{
  return QString::number (stream_status.linkRate);
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
void Rx::RxThread::setSampleFormat (int sampleFormat)
{
  switch(sampleFormat)
    {
      case FORMAT_12BIT_INT:
        {
        qDebug()<<"Stream Sample Format set to 12-bit integers,";
        rx_stream.dataFmt = lms_stream_t::LMS_FMT_I12;
        break;
      }
      case FORMAT_16BIT_INT:
        {
        qDebug()<<"Stream Sample Format set to 16-bit integers,";
        rx_stream.dataFmt = lms_stream_t::LMS_FMT_I16;
        break;
      }
      case FORMAT_32BIT_FLOAT:
        {
        qDebug()<<"Stream Sample Format set to 32-bit float";
        rx_stream.dataFmt = lms_stream_t::LMS_FMT_F32;
        break;
        }
    default:
      {
      rx_stream.dataFmt = lms_stream_t::LMS_FMT_F32;
      break;
      }
    }
}

void Rx::RxThread::setLNAGain (size_t channel, int gain)
{
  if(gain > 30)
    {
      gain = 30;
    }
  rx_lna_gain = gain;
  if(bStreamActive)
    {
      int result = LMS_WriteParam(lime_device,LMS7param(G_LNA_RFE),gain);
    }
}

void Rx::RxThread::setPGAGain (size_t channel, int gain)
{
  if(gain < -12)
    {
      gain = -12;
    }
  else if(gain > 19)
    {
      gain = 19;
    }
  rx_pga_gain = gain;
  if(bStreamActive)
    {
      int result = LMS_WriteParam(lime_device,LMS7param(G_PGA_RBB),gain);
    }
}

void Rx::RxThread::setTIAGain (size_t channel,int gain)
{
  if(gain > 12)
    {
    gain = 12;
    }
  rx_tia_gain = gain;
  if(bStreamActive)
    {
    int result = LMS_WriteParam(lime_device,LMS7param(G_TIA_RFE),gain);
    }
}
void Rx::RxThread::setPlotUpdateType (int update)
{
  if(update == 0)
    {
    plotUpdateTimed = true;
    qDebug()<<"Timed Plot Update enabled";
    }
  else if(update == 1)
    {
    plotUpdateTimed = false;
    std::cout << "Timed Plot update disabled";
    }
}
