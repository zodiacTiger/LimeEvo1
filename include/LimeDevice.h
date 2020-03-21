#ifndef LIMEDEVICE_H
#define LIMEDEVICE_H

#include "LimeRadio.hpp"

 class LimeDevice : public LimeRadio{


 public:

   struct lms_radio_config{
     double freq = 1000000;
     double sampleRate = 2000000;
     double bandwidth = 8e6;
     int gain = 50;
     bool isTX = false;
     std::string rxChannel = "LNAW";
   };

  LimeDevice ();
  ~LimeDevice ();

  static bool deviceFound ();
  static std::string lms_device_error(lms_device_t *d);
  std::string boardTemp ();

};

#endif // LIMEDEVICE_H
