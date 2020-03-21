//
// Created by ZodiacTiger on 2/21/20.
//

#include "StreamTimer.hpp"
#include <QDebug>

bool bUpdate = false;

StreamTimer::StreamTimer ()
{
  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(StreamTimerSlot ()));
  bUpdate=false;
  timer->start(1000);
}

bool StreamTimer::StreamTimerSlot()
{
  qDebug() << "Timer";
  bUpdate = true;
  return bUpdate;
}

bool StreamTimer::getUpdate()
{
  return true;
}