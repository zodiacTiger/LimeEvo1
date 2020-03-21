//
// Created by ZodiacTiger on 3/9/20.
//

#ifndef LIMEEVO1_RADIORTLSDR_HPP
#define LIMEEVO1_RADIORTLSDR_HPP

#include "Radios.h"

class RtlSdrRadio: public Radios {
 public:
  RtlSdrRadio();
  ~RtlSdrRadio ();
  int setup();
 private:
};

#endif //LIMEEVO1_RADIORTLSDR_HPP
