//
// Created by ZodiacTiger on 1/21/20.
//

#ifndef LIMEEVO1_LIMERADIO_HPP
#define LIMEEVO1_LIMERADIO_HPP
#include <lime/LimeSuite.h>
#include <iostream>
#include <QObject>
#include <QString>
#include <QDebug>
 class LimeRadio{
 public:

  LimeRadio ();
   lms_device_t *lmsdevice = nullptr;
   lms_dev_info_t device_info_list[8];
   static void find (lms_device_t *d, lms_info_str_t device_info_list[8]);
  static lms_device_t showStatus (int i, lms_info_str_t device_info_list[8]);
  static std::string status (int i, lms_device_t *d, lms_info_str_t device_info_list[8]);
  lms_device_t *getDevice();

  ~LimeRadio ();
  static QString QTStatus (int i, void *d, lms_info_str_t *device_info_list);
  static QString QTShowConnectedDevice ();
  static bool DeviceConnected();

};

#endif //LIMEEVO1_LIMERADIO_HPP
