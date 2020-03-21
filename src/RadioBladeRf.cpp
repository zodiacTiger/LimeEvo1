//
// Created by ZodiacTiger on 3/9/20.
//

#include "RadioBladeRf.hpp"
#include "Radios.h"
#include <libbladeRF.h>

BladeRFRadio::BladeRFRadio ()
{
  std::cout << "BladeRF Constructor";

}

BladeRFRadio::~BladeRFRadio ()
{

}

int BladeRFRadio::setup ()
{
  std::cout << "BladeRF Setup Called.\n";
  int status;

//  rx_config->channel="RX1";
  rx_config.frequency = 100000000;
  rx_config.channel=BLADERF_CHANNEL_RX (1);
  rx_config.gain= 30;
  rx_config.samplerate=2000000;
  rx_config.bandwidth=2000000;

  deviceStatus.rx_0_samplerate=rx_config.samplerate;
  deviceStatus.rx_0_freq=rx_config.frequency;
  deviceStatus.rx_0_enabled=true;

  bladerf_devinfo dev_info;
  bladerf_init_devinfo (&dev_info);
  status = bladerf_open_with_devinfo (&dev,&dev_info);

  std::cout << "Setting up RX\n";

  status = bladerf_set_frequency(dev, rx_config.channel, rx_config.frequency);
  if (status != 0) {
    fprintf(stderr, "Failed to set frequency = %u: %s\n", rx_config.frequency,
            bladerf_strerror(status));
//    return status;
    }

  status = bladerf_set_sample_rate(dev, rx_config.channel, rx_config.samplerate, NULL);
  if (status != 0) {
    fprintf(stderr, "Failed to set samplerate = %u: %s\n", rx_config.samplerate,
            bladerf_strerror(status));
//    return status;
    }

  status = bladerf_set_bandwidth(dev, rx_config.channel, rx_config.bandwidth, NULL);
  if (status != 0) {
    fprintf(stderr, "Failed to set bandwidth = %u: %s\n", rx_config.bandwidth,
            bladerf_strerror(status));
//    return status;
    }

  status = bladerf_set_gain(dev, rx_config.channel, rx_config.gain);
  if (status != 0) {
    fprintf(stderr, "Failed to set gain: %s\n", bladerf_strerror(status));
//    return status;
    }



std::cout << "Setting up TX\n";
  tx_config.channel=BLADERF_CHANNEL_TX(0);
  tx_config.frequency=123999999;
  tx_config.bandwidth=2000000;
  tx_config.samplerate=2000000;
  tx_config.gain = 12;

  status = bladerf_set_frequency(dev, tx_config.channel, tx_config.frequency);
  if (status != 0) {
    fprintf(stderr, "Failed to set frequency = %u: %s\n", tx_config.frequency,
            bladerf_strerror(status));
//    return status;
    }

  status = bladerf_set_sample_rate(dev, tx_config.channel, tx_config.samplerate, NULL);
  if (status != 0) {
    fprintf(stderr, "Failed to set samplerate = %u: %s\n", tx_config.samplerate,
            bladerf_strerror(status));
//    return status;
    }

  status = bladerf_set_bandwidth(dev, tx_config.channel, tx_config.bandwidth, NULL);
  if (status != 0) {
    fprintf(stderr, "Failed to set bandwidth = %u: %s\n", tx_config.bandwidth,
            bladerf_strerror(status));
//    return status;
    }

  status = bladerf_set_gain(dev, tx_config.channel, tx_config.gain);
  if (status != 0) {
    fprintf(stderr, "Failed to set gain: %s\n", bladerf_strerror(status));
//    return status;
    }
  return 1;
}



void BladeRFRadio::close_device ()
{
  std::cout << "\nBladeRF Closed";
  bladerf_close (dev);
}
BladeRFRadio::device_status BladeRFRadio::getDeviceStatus ()
{
  std::cout << "\nDevice Status";
  return deviceStatus;
}

