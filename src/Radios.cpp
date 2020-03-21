//
// Created by ZodiacTiger on 3/9/20.
//

#include "Radios.h"
#include <RadioBladeRf.hpp>
#include <libbladeRF.h>
#include <iostream>
Radios::Radios ()
{
}

Radios::~Radios ()
{

}

int Radios::setup ()
{
  std::cout << "Base Radio Called.";
  return 0;
}

void Radios::close_device ()
{

}