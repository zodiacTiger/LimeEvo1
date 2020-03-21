//
// Created by ZodiacTiger on 2/17/20.
//

#ifndef LIMEEVO1_LIMESTREAMRX_HPP
#define LIMEEVO1_LIMESTREAMRX_HPP

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <complex>
#include <lime/LimeSuite.h>

class LimeStreamRX : public QObject {
  Q_OBJECT

 public:
  explicit LimeStreamRX(lms_device_t *d);
  ~LimeStreamRX ();
};

#endif //LIMEEVO1_LIMESTREAMRX_HPP
