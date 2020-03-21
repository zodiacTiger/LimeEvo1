//
// Created by ZodiacTiger on 3/9/20.
//

#ifndef LIMEEVO1_RADIOBLADERF_HPP
#define LIMEEVO1_RADIOBLADERF_HPP
#include "Radios.h"
#include <iostream>
#include <libbladeRF.h>
class BladeRFRadio: public Radios {

 public:
  struct bladerf *dev=nullptr;

  struct channel_config{
    bladerf_channel channel;
    unsigned int frequency;
    unsigned int bandwidth;
    unsigned int samplerate;
    int gain;
  };
  struct device_status{
    bool rx_0_enabled;
    bool rx_1_enabled;
    unsigned int rx_0_freq;
    unsigned int tx_0_freq;
    unsigned int rx_0_samplerate;
    unsigned int tx_0_samplerate;
  };
  channel_config rx_config;
  channel_config tx_config;
  device_status deviceStatus;

  device_status getDeviceStatus();
  void close_device();
  BladeRFRadio();
  ~BladeRFRadio ();
  int setup();
 private:
  std::string RadioLabel = "BladeRF Radio";
};

#endif //LIMEEVO1_RADIOBLADERF_HPP
