//
// Created by ZodiacTiger on 1/21/20.
//

#include "LimeRadio.hpp"
#include <QDebug>
#include <iostream>
#include <lime/LimeSuite.h>
#include <cmath>
#include <string>
#include <QApplication>
#include <LimeDevice.h>

LimeRadio::LimeRadio ()
{
  int ret;
  lms_info_str_t *device_info_list = new lms_info_str_t[8];

  if ((ret = LMS_GetDeviceList (device_info_list)) < 0)
    {
    std::cout << "ERROR --> " << LMS_GetLastErrorMessage ();
    LimeDevice::lms_device_error(lmsdevice);
    }
  std::cout << "Found Lime Device\n";
  std::cout << device_info_list[0] << "\n";

  if (ret < 1)
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
  delete []device_info_list;
}

void LimeRadio::find (lms_device_t *lmsDevice, lms_info_str_t device_info_list[8])
{
  std::cout << "\n================================================\n";
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&lmsDevice, device_info_list[0], NULL);
  std::cout << "\n" << device_info_list[0] << "\n";
  std::cout << "\n================================================\n";

  LMS_Close (lmsDevice);

}

lms_device_t LimeRadio::showStatus (int deviceIndex, lms_info_str_t device_info_list[8])
{
  std::cout << "DEVICE STRING --> " << device_info_list[deviceIndex];
}

std::string LimeRadio::status (int deviceIndex, lms_device_t *d, lms_info_str_t device_info_list[8])
{

  std::cout << "\nGETTING DEVICE LIST\n";
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&d, device_info_list[0], NULL);
  std::string currentDevice = device_info_list[deviceIndex];
  LMS_Close (d);
  return currentDevice;
}

QString LimeRadio::QTStatus (int deviceIndex, lms_device_t *lmsDevice, lms_info_str_t device_info_list[8])
{
  std::cout << "\nGETTING DEVICE LIST\n";
  QString currentDeviceID;

  if(LMS_GetDeviceList (device_info_list) !=0)
    {
      LMS_Open (&lmsDevice, device_info_list[0], nullptr);
      currentDeviceID = QString::fromStdString (device_info_list[deviceIndex]);
      LMS_Close (lmsDevice);
    }
  else{
    std::cerr << "\n[WARNING] Lime Device Not Found.\n";
    currentDeviceID = "[WARNING] Lime Device Not Found.";
  }
  return currentDeviceID;
}

QString LimeRadio::QTShowConnectedDevice ()
{
  lms_info_str_t *device_info_list = new lms_info_str_t[8];
  std::cout << "\nGETTING DEVICE LIST\n";
  QString currentDeviceID;
  if(LMS_GetDeviceList (device_info_list) !=0)
    {
      currentDeviceID = QString::fromStdString (device_info_list[0]);
    }
  else
    {
      std::cerr << "\n[WARNING] Lime Device Not Found.\n";
      currentDeviceID = "[WARNING] Lime Device Not Found.";
    }
  return currentDeviceID;
}


bool LimeRadio::DeviceConnected ()
{
  lms_device_t *d = nullptr;
  lms_info_str_t *device_info_list=new lms_info_str_t[8];
  LMS_GetDeviceList (device_info_list);

  if(LMS_Open (&d, device_info_list[0], NULL)!=0)
    {
    delete [] device_info_list;
    return false;
    }
  else{
    LMS_Close (d);
    delete [] device_info_list;
    return true;
  }
}
lms_device_t *LimeRadio::getDevice ()
{
  return lmsdevice;
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

