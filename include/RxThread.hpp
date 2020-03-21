//
// Created by ZodiacTiger on 2/7/20.
//

#ifndef LIMEEVO1_RXTHREAD_HPP
#define LIMEEVO1_RXTHREAD_HPP
#include <QThread>
#include <QObject>
#include <lime/LimeSuite.h>
#include <complex>

#define RX_OUTPUT_FILENAME "./test.data"


namespace Rx
{
 class RxThread: public QThread
    {
     private:
      bool bStopped=false;
      QMutex *mutex;

     public:

explicit RxThread (double freq, bool rxToFile);
explicit RxThread (QMutex *mutex,double freq, unsigned int rx_gain, double sampRate, const double streamRate, size_t rxChannel, size_t rxAntenna, bool rxToFile);
explicit RxThread (double freq, unsigned int rx_gain, double sampRate, const double streamRate, bool rxToFile);
~RxThread ();

  FILE* fd = stdout;
   bool bStreamActive = false;
   const unsigned int fifo_size = 2048 * 2048;
   double stream_rate = 0.3;
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
   static const int bufferSize=10000;
   std::complex<float> buffer[bufferSize];


   lms_device_t *lime_device=nullptr;
   lms_stream_t rx_stream;
   lms_stream_status_t stream_status;
   lms_stream_meta_t rx_meta;

  void stop();
  void run();

  QString getCurrentGain();
  QString setFreq(double freq, size_t channel, size_t path);
  QString setGain(unsigned int gain,size_t channel);
  QString setAntennaStreaming(size_t channel, int antenna_index);
  QString setAntenna(size_t channel, int antenna_index);
  QString getFreq();
  QString getDataRate();
  QString getSampleRate();
  QString getOverruns();
  QString getTotalSamples();
  QString getDroppedPackets();
  int setStreamLatency(double rate);
  int setSampleRate(double rate);


  int setRegister(int address,int value);
  lms_stream_status_t getStreamStatus();
  void setRXToFile(bool rxToFile);
  void disableStream();
  QString getRXSample();
  std::complex<float> getRXSampleComplex();
  std::complex<float> tempRXSamp;

  public slots:

 signals:
   QString getTotalSamples (size_t channel);
 };
}
#endif //LIMEEVO1_RXTHREAD_HPP
