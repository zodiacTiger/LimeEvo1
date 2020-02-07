//
// Created by ZodiacTiger on 1/21/20.
//

#ifndef LIMEEVO1_LIMERADIO_HPP
#define LIMEEVO1_LIMERADIO_HPP
#include <lime/LimeSuite.h>
#include <iostream>
#include <QString>

class LimeRadio {

 public:
  LimeRadio ();
  static void find (lms_device_t *d, lms_info_str_t device_info_list[8]);
  static lms_device_t showStatus (int i, lms_info_str_t device_info_list[8]);
  static std::string status (int i, lms_device_t *d, lms_info_str_t device_info_list[8]);
  void startRXstream (lms_device_t *d);
  void configureRX (lms_device_t *d, lms_info_str_t *dlist, int channel, float samp_rate, double freq);

  ~LimeRadio ();
  static QString QTStatus (int i, void *d, lms_info_str_t *device_info_list);
};

#endif //LIMEEVO1_LIMERADIO_HPP
