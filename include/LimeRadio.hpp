//
// Created by ZodiacTiger on 1/21/20.
//

#ifndef LIMEEVO1_LIMERADIO_HPP
#define LIMEEVO1_LIMERADIO_HPP
#include <lime/LimeSuite.h>
#include <iostream>
class LimeRadio {
 public:
  LimeRadio();
  static void find(lms_device_t *d, lms_info_str_t dlist[8]);

  static lms_device_t showStatus(int i);
  std::string status(int i);
};

#endif //LIMEEVO1_LIMERADIO_HPP
