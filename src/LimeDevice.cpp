//
// Created by ZodiacTiger on 1/21/20.
//

#include "LimeDevice.h"
#include "LimeRadio.hpp"
#include <QDebug>
#include <iomanip>
#include <cmath>

LimeDevice::LimeDevice ()
= default;

LimeDevice::~LimeDevice ()
= default;
std::string LimeDevice::lms_device_error (lms_device_t *device)
{
  std::cout << "ERROR --> " << LMS_GetLastErrorMessage ();
  if (device != NULL)
    {
    LMS_Close (device);
    exit(-1);
    }
  return LMS_GetLastErrorMessage ();
}

bool LimeDevice::deviceFound ()
{
  std::cout << "\n================================================\n";
  std::cout << "\n          Quick Check for Lime Device           \n";
  std::cout << "\n================================================\n";
  lms_info_str_t device_info_list[8];

  bool deviceFound = false;
  if (!LMS_GetDeviceList (device_info_list))
    {
    deviceFound = false;
    std::cout << "              No Device Found                   ";
    }
  else
    {
    deviceFound = true;
    std::cout << "                Device Found                    ";
    std::cout << "\n" << device_info_list[0] << "\n";
    }
  std::cout << "\n================================================\n";

  return deviceFound;
}

std::string LimeDevice::boardTemp ()
{
  qDebug () << "Rx Stream Called";

  lms_info_str_t device_info_list[8];
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&lmsdevice, device_info_list[0], NULL);
  if (LMS_Init (lmsdevice))
    {
      lms_device_error (lmsdevice);
    }
  else
    {
    std::cout << "Device Initialized";
    }
  double temp = 0.0;

  LMS_GetChipTemperature (lmsdevice, 0, &temp);
  double rounded_temp = std::floor ((temp * 100) + .5) / 100;

  qDebug () << "\nLIME DEVICE :: Chip Temperature" << temp << " C";
  if (LMS_Reset (lmsdevice) == 0)
    {
    qDebug () << "LIME DEVICE :: Reset ";
    }
  LMS_Close (lmsdevice);
  return std::to_string (rounded_temp);
};

