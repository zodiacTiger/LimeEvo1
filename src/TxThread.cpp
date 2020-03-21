//
// Created by ZodiacTiger on 2/25/20.
//
#include <lime/LimeSuite.h>
#include <QString>
#include <QDebug>
#include <mutex>
#include "TxThread.hpp"
#include <cmath>

Tx::TxThread::TxThread (double freq, unsigned int gain, double sampRate, const double streamRate, size_t txChannel, size_t txAntenna, bool txToFile)
{
  center_freq = freq;
  tx_gain = gain;
  samp_rate = sampRate;
  stream_rate = streamRate;
  channel = txChannel;
  antenna = txAntenna;
  tx_to_file = txToFile;
}
Tx::TxThread::TxThread (double freq, unsigned int gain, double sampRate, const double streamRate, bool txToFile)
{
  center_freq = freq;
  tx_gain = gain;
  samp_rate = sampRate;
  stream_rate = streamRate;
}

Tx::TxThread::~TxThread ()
{

}

void Tx::TxThread::run()
{
  this->setPriority (TxThread::HighestPriority);

  auto startTime = std::chrono::high_resolution_clock::now ();
  auto timeLimit = std::chrono::high_resolution_clock::now ();
  auto timeLastStatus = std::chrono::high_resolution_clock::now ();

  lms_info_str_t devInfo[8];
  LMS_GetDeviceList (devInfo);

  if(LMS_Open (&lime_device,devInfo[0], nullptr) != 0)
    {
    qDebug() << "\n[LIME DEVICE] Unable to open device.\n";
    }
  else
    {
    LMS_Init (lime_device);
    qDebug () << "[LIME DEVICE] Initialized.";
    LMS_EnableChannel (lime_device, LMS_CH_TX, channel, true);
    qDebug () << "[LIME DEVICE] Rx Channel " << "0" << " Enabled";
    LMS_SetSampleRate (lime_device, samp_rate, 2);
    qDebug () << "[LIME DEVICE] Sample rate set at " << samp_rate << " Ms/s";
    LMS_SetLOFrequency (lime_device, LMS_CH_TX, channel, center_freq);
    qDebug () << "[LIME DEVICE] Freq set at " << center_freq << " Hz";
    LMS_SetAntenna (lime_device, LMS_CH_TX, channel, antenna);
    qDebug () << "[LIME DEVICE] Antenna set at -> " << antenna << "";
    qDebug () << "[LIME DEVICE] LPF set at " << bw << " Hz";
    LMS_SetLPFBW (lime_device, LMS_CH_TX, channel, bw);
    LMS_SetNormalizedGain (lime_device, LMS_CH_TX, channel, 0);
    qDebug () << "[LIME DEVICE] Normalized Gain set at " << "0" << " db";
    LMS_SetGaindB (lime_device, LMS_CH_TX, channel, tx_gain);
    qDebug () << "[LIME DEVICE] Gain set at " << tx_gain << " db";
    qDebug () << "[LIME DEVICE] Calibrating for " << samp_rate << " Ms/s";
    LMS_Calibrate (lime_device, LMS_CH_TX, channel, bw, 0);
    // test signal
//    LMS_SetTestSignal (lime_device, LMS_CH_TX, 0, LMS_TESTSIG_NONE, 0, 0);
    }

    totalSamples = 0;
    const int tx_bufferSize=10000;

//    float *tx_buffer[tx_bufferSize * 2];
  float tx_buffer[tx_bufferSize * 2];

  for (int i = 0; i <tx_bufferSize; i++)
    {
      tx_buffer[2*i] = cos(2*M_PI*i/16.0);
      tx_buffer[2*i+1] = sin(2*M_PI*i/16.0);
    }

  tx_stream.channel = channel;
  tx_stream.fifoSize=4096 * 4096;
  tx_stream.throughputVsLatency=stream_rate;
  tx_stream.dataFmt = lms_stream_t::LMS_FMT_F32;
  tx_stream.isTx = true;
  tx_meta.waitForTimestamp=false;
  tx_meta.flushPartialPacket=false;
  tx_meta.timestamp=0;
  if(LMS_SetupStream (lime_device,&tx_stream) !=0)
    {
      qDebug()<<"[LIME TX] Error Setup in stream.";
    bStreamActive = false;
    }
  else{
    qDebug()<<"[LIME TX] Stream Setup Successfully.";
    if(LMS_StartStream(&tx_stream) !=0)
      {
        qDebug()<<"[LIME TX] Error Starting Stream.";
      }
    else{
        qDebug()<<"[LIME TX] Stream Started.";
        bStreamActive = true;
      }
  }
  while(bStreamActive)
  {
    int ret = LMS_SendStream (&tx_stream,tx_buffer,tx_bufferSize,&tx_meta,3000);
  }
  qDebug()<<"[LIME TX] Closing & Destroying stream.";
  LMS_StopStream (&tx_stream);
  LMS_DestroyStream (lime_device,&tx_stream);
  LMS_Reset (lime_device);
  LMS_Close (lime_device);
}

void Tx::TxThread::disableStream()
{
  bStreamActive = false;
  qDebug()<<"[LIME TX] ]Stream Disabled.";
}

void Tx::TxThread::stop()
{

}

Tx::TxThread::TxThread ()
{

}

void Tx::TxThread::setGain (int gain,size_t chan)
{
  tx_gain = gain;
  channel = chan;
  if(bStreamActive)
    {
    if (LMS_SetGaindB (lime_device, LMS_CH_TX, channel, tx_gain) != 0)
      {
        qDebug () << "[LIME TX] Error setting gain.";
      }
    else
      {
        qDebug () << "[LIME TX] Gain Set to " << tx_gain;
      }
    }
}

void Tx::TxThread::setFreq (double freq, size_t chan)
{
  center_freq=freq;
  channel=chan;
  if(bStreamActive)
    {
    if (LMS_SetLOFrequency (lime_device, LMS_CH_TX, chan, center_freq) != 0)
      {
        qDebug () << "[LIME TX] Error setting frequency.";
      }
    else
      {
        qDebug () << "[LIME TX] Freq Set to " << center_freq;
      }
    }

}

QString Tx::TxThread::getGain()
{
  return QString::number (tx_gain);
}

QString Tx::TxThread::getFreq ()
{
  return QString::number (center_freq,'f');
}

