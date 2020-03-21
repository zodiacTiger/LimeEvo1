//
// Created by ZodiacTiger on 3/12/20.
//

#ifndef LIMEEVO1_RXTHREADCONCURRENT_HPP
#define LIMEEVO1_RXTHREADCONCURRENT_HPP

#include <QThread>
#include <qtconcurrentrun.h>
#include <lime/LimeSuite.h>

class RxThreadConcurrent {


  explicit RxThreadConcurrent (double freq, unsigned int rx_gain, double sampRate, const double streamRate, size_t rxChannel, size_t rxAntenna, bool rxToFile);

 public:

  FILE* fd = stdout;
  bool bStreamActive = false;
  const unsigned int fifo_size = 16384 * 16384;
  double stream_rate = 0.5;
  unsigned int rx_gain = 60;
  unsigned int overruns=0;
  unsigned int underruns=0;
  unsigned int droppedPackets=0;
  unsigned long long totalSamples=0;
  double samp_rate = 2e6;
  const float bw=2.5e6;
  float data_rate = 0.0;
  size_t channel = 0;
  size_t antenna = LMS_PATH_LNAW;
  bool rx_to_file = true;
  double center_freq = 1938800000;
  float FIFOstatus=0.0;


  lms_device_t *lime_device=nullptr;
  lms_stream_t rx_stream;
  lms_stream_status_t stream_status;
  lms_stream_meta_t rx_meta;




};

#endif //LIMEEVO1_RXTHREADCONCURRENT_HPP
