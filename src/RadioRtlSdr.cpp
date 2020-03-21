//
// Created by ZodiacTiger on 3/9/20.
//

#include "RadioRtlSdr.hpp"
#include <iostream>

RtlSdrRadio::RtlSdrRadio ()
{
  std::cout << "Rtl Sdr Constructor";
}

RtlSdrRadio::~RtlSdrRadio ()
{

}

int RtlSdrRadio::setup ()
{
  std::cout << "Rtl-Sdr Radio setup.";
  return 2;
}