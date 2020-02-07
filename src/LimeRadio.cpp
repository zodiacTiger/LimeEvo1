//
// Created by ZodiacTiger on 1/21/20.
//

#include "LimeRadio.hpp"
#include <QDebug>
#include <iostream>
#include <chrono>
#include <lime/LimeSuite.h>
#include <cmath>
#include <string>
#include <QApplication>
#include <LimeDevice.h>

LimeRadio::LimeRadio ()
{
  lms_device_t *lmsdevice = NULL;
  int n;
  lms_info_str_t device_info_list[8];

  if ((n = LMS_GetDeviceList (device_info_list)) < 0)
    {
    std::cout << "ERROR --> " << LMS_GetLastErrorMessage ();
    LimeDevice::lms_device_error(lmsdevice);
    }

  std::cout << "Found Lime Device\n";
  std::cout << device_info_list[0] << "\n";

  if (n < 1)
    {
    std::cout << "No Device Found.";
    }
  if (LMS_Open (&lmsdevice, device_info_list[0], NULL))
    {
    LimeDevice::lms_device_error(lmsdevice);
    }
//  LMS_LoadConfig (lmsdevice,"path to config file");
  if (LMS_Init (lmsdevice) != 0)
    {
    LimeDevice::lms_device_error(lmsdevice);
    }
  std::cout << "Device Initialized.";
  LMS_Close (lmsdevice);
}

void LimeRadio::find (lms_device_t *d, lms_info_str_t device_info_list[8])
{
  std::cout << "\n================================================\n";
//    device_info_list[0] = dlist[0];
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&d, device_info_list[0], NULL);
  std::cout << "\n" << device_info_list[0] << "\n";
  std::cout << "\n================================================\n";

  LMS_Close (d);

}

lms_device_t LimeRadio::showStatus (int i, lms_info_str_t device_info_list[8])
{
  std::cout << "DEVICE STRING --> " << device_info_list[i];

}

std::string LimeRadio::status (int i, lms_device_t *d, lms_info_str_t device_info_list[8])
{

  std::cout << "\nGETTING DEVICE LIST\n";
  lms_dev_info_t dInfo;
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&d, device_info_list[0], NULL);
  std::string currentDevice = device_info_list[i];
  LMS_Close (d);
  return currentDevice;
}

QString LimeRadio::QTStatus (int i, lms_device_t *d, lms_info_str_t device_info_list[8])
{
  std::cout << "\nGETTING DEVICE LIST\n";
  lms_dev_info_t dInfo;
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&d, device_info_list[0], NULL);
  QString currentDevice = QString::fromStdString (device_info_list[i]);
  LMS_Close (d);
  return currentDevice;
}

void LimeRadio::startRXstream (lms_device_t *d)
{
  lms_info_str_t device_info_list[8];

  LMS_GetDeviceList (device_info_list);
  std::cout << "DEVICE INFO ----> " << device_info_list[0];

}

void LimeRadio::configureRX (lms_device_t *d, lms_info_str_t *dlist, int channel, float samp_rate, float_type freq)
{
  lms_info_str_t device_info_list[8];
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&d, device_info_list[0], NULL);
  if (LMS_Init (d))
    {
    LimeDevice::lms_device_error(d);
    LimeDevice::lms_device_error(d);
    }
  else
    {
    std::cout << "Device Initialized";
    }
  if (LMS_EnableChannel (d, LMS_CH_RX, 0, true) != 0)
    {
    LimeDevice::lms_device_error(d);
    }
  else
    {
    std::cout << "Channel Configured";
    }
  if (LMS_SetLOFrequency (d, LMS_CH_RX, 0, freq) != 0)
    {
    LimeDevice::lms_device_error(d);
    }
  else
    {
    std::cout << "Frequency set at " << freq;
    }
  if (LMS_SetSampleRate (d, samp_rate, 2) != 0)
    {
    LimeDevice::lms_device_error(d);
    }
  double temp = 0.0;
  LMS_GetChipTemperature (d, 0, &temp);
  qDebug () << "\nLIME DEVICE :: Chip Temperature" << temp << " C";
  if (LMS_Reset (d) == 0)
    {
    qDebug () << "LIME DEVICE :: Reset ";
    }
  LMS_Close (d);

}

LimeRadio::~LimeRadio ()
= default;

short sine_generator (int samples)
{
  short idata[samples];
  short qdata[samples];
  for (int i = 0; i < samples; i++)
    {
    idata[i] = 32768 * sin ((2 * 3.14 * i) / samples);
    qdata[i] = 32768 * cos ((2 * 3.14 * i) / samples);
    }
  return 0;
}

