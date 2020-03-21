//
// Created by ZodiacTiger on 2/18/20.
//

#ifndef LIMEEVO1_HELPERS_HPP
#define LIMEEVO1_HELPERS_HPP

#include <QElapsedTimer>
#include <QCoreApplication>

static void wait (float sec)
{
  QElapsedTimer timer;
  timer.start ();
  while (!timer.hasExpired (sec * 1000))
    QCoreApplication::processEvents ();
}
#endif //LIMEEVO1_HELPERS_HPP
