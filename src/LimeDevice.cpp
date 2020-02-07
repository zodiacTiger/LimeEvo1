//
// Created by ZodiacTiger on 1/21/20.
//

#include "LimeDevice.h"
#include "LimeRadio.hpp"
#include <iomanip>
#include <cmath>
lms_device_t *d = NULL;
lms_info_str_t dlist[8];

LimeDevice::LimeDevice ()
= default;

LimeDevice::~LimeDevice ()
= default;

int LimeDevice::lms_device_error (lms_device_t *device)
{
  std::cout << "ERROR --> " << LMS_GetLastErrorMessage ();
  if (device != NULL)
    {
    LMS_Close (device);
    exit (-1);
    }
  return 0;
}

bool LimeDevice::deviceFound ()
{
  std::cout << "\n================================================\n";
  std::cout << "\n          Quick Check for Lime Device           \n";
  std::cout << "\n================================================\n";

  bool deviceFound = false;
  if (!LMS_GetDeviceList (dlist))
    {
    deviceFound = false;
    std::cout << "              No Device Found                   ";
    }
  else
    {
    deviceFound = true;
    std::cout << "                Device Found                    ";
    std::cout << "\n" << dlist[0] << "\n";
    }
  std::cout << "\n================================================\n";

  return deviceFound;
}

//QString LimeDevice::QLMSBoardTemp(){
//  std::string temp;
//  LimeRadio r;
//}

void LimeDevice::on_device_info_clicked ()
{
  qDebug () << "Device Info Called";
  LimeRadio::status (0, d, dlist);
};

std::string LimeDevice::boardTemp ()
{
  qDebug () << "Rx Stream Called";

  lms_info_str_t device_info_list[8];
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&d, device_info_list[0], NULL);
  if (LMS_Init (d))
    {
      lms_device_error (d);
    }
  else
    {
    std::cout << "Device Initialized";
    }
  double temp = 0.0;

  LMS_GetChipTemperature (d, 0, &temp);
  double rounded_temp = std::floor ((temp * 100) + .5) / 100;

  qDebug () << "\nLIME DEVICE :: Chip Temperature" << temp << " C";
  if (LMS_Reset (d) == 0)
    {
    qDebug () << "LIME DEVICE :: Reset ";
    }
  LMS_Close (d);
  return std::to_string (rounded_temp);
};

void LimeDevice::on_gui_buttons_enabled ()
{
  this->dumpObjectInfo ();
}
void LimeDevice::on_tx_stream_clicked ()
{
  qDebug () << "Tx Stream Called";
}

void LimeDevice::on_tx_test_sine_clicked ()
{
  qDebug () << "Tx Test Sine Called";
  emit emit_test ();
};

void LimeDevice::on_exit_clicked ()
{
  qDebug () << "Exit Called";
  exit (0);
}

void LimeDevice::emit_test ()
{
  qDebug () << "EMIT";
}

void LimeDevice::on_load_cfg_clicked ()
{
  qDebug () << "LOAD CONFIG Clicked";
}

void LimeDevice::receiveFromQML ()
{
  qDebug () << "Received from QML";
}


