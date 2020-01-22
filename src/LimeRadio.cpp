//
// Created by ZodiacTiger on 1/21/20.
//

#include "LimeRadio.hpp"
#include <iostream>
#include <chrono>
#include <lime/LimeSuite.h>
#include <math.h>
#include <string>

int error(lms_device_t *device)
{
  std::cout << "ERROR --> " << LMS_GetLastErrorMessage();
  if(device != NULL)
    {
    LMS_Close(device);
    exit(-1);
    }
  return 0;
}

lms_device_t *lmsdevice = NULL;
int n;
lms_info_str_t device_info_list[8];

  LimeRadio::LimeRadio()
  {

    if ((n = LMS_GetDeviceList (device_info_list)) < 0)
      {
      std::cout << "ERROR --> " << LMS_GetLastErrorMessage ();
        error(lmsdevice);
      }

    std::cout << "Found Lime Device\n";
    std::cout << device_info_list[0] << "\n";

    if (n < 1)
      {
        std::cout << "No Device Found.";
      }
    if (LMS_Open (&lmsdevice, device_info_list[0], NULL))
      {
        error (lmsdevice);
      }
//  LMS_LoadConfig (lmsdevice,"path to config file");
    if (LMS_Init (lmsdevice) != 0)
      {
        error (lmsdevice);
      }
    std::cout << "Device Initialized.";
    LMS_Close (lmsdevice);
  }


void LimeRadio::find(lms_device_t *d, lms_info_str_t dlist[8])
  {
    std::cout << "\n================================================\n";
    lmsdevice = d;
//    device_info_list[0] = dlist[0];
    LMS_GetDeviceList (dlist);
    LMS_Open (&d,dlist[0],NULL);
  std::cout << "\n"<< dlist[0] << "\n";
  std::cout << "\n================================================\n";

  LMS_Close (d);

  }

lms_device_t LimeRadio::showStatus(int i)
{
  std::cout << "DEVICE STRING --> " << device_info_list[i];
}

std::string LimeRadio::status(int i)
{
  std::cout << "\nGETTING DEVICE LIST\n";
  lms_dev_info_t dInfo;
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&lmsdevice,device_info_list[0],NULL);
  std::string currentDevice = device_info_list[i];
  return currentDevice;
}




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

