//
// Created by ZodiacTiger on 3/9/20.
//

#ifndef LIMEEVO1_RADIOS_H
#define LIMEEVO1_RADIOS_H

class Radios {

 public:
  Radios();
  ~Radios();
  virtual int setup();
  virtual void close_device();

};

#endif //LIMEEVO1_RADIOS_H
