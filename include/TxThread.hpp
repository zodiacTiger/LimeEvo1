//
// Created by ZodiacTiger on 2/25/20.
//

#ifndef LIMEEVO1_TXTHREAD_HPP
#define LIMEEVO1_TXTHREAD_HPP

#include <QThread>
#include <lime/LimeSuite.h>

namespace Tx
{
class TxThread : public QThread {

 public:
  // meta stats
  unsigned int overruns=0;
  unsigned int underruns=0;
  unsigned int droppedPackets=0;
  unsigned long long totalSamples=0;

  // stream & device settings
  const unsigned int fifo_size = 8192 * 8192;
  bool bStreamActive = false;
  unsigned int tx_gain = 0;
  double stream_rate = 0.5;
  double samp_rate = 8e6;
  float bw=8e6;
  float data_rate = 0.0;
  size_t channel = 0;
  size_t antenna = LMS_PATH_TX1;
  bool tx_to_file = true;
  double center_freq = 1066467447;
  float FIFOstatus=0.0;

  lms_stream_t tx_stream;
  lms_stream_status_t stream_status;
  lms_stream_meta_t tx_meta;
  lms_device_t *lime_device =nullptr;

  explicit TxThread ();
  explicit TxThread (double freq);
  explicit TxThread (double freq, unsigned int tx_gain, double sampRate, const double streamRate, size_t txChannel, size_t txAntenna, bool txToFile);

  explicit TxThread (double freq, unsigned int tx_gain, double sampRate, const double streamRate, bool txToFile);
  ~ TxThread ();
  void setGain(int gain,size_t chan);
  void setFreq(double freq,size_t chan);
  QString getGain();
  QString getFreq();
  void disableStream();
  void run () override;
  void stop ();
};
}
#endif //LIMEEVO1_TXTHREAD_HPP
