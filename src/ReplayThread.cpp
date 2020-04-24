//
// Created by ZodiacTiger on 4/22/20.
//

#include "ReplayThread.hpp"
ReplayThread::ReplayThread ()
{

}
ReplayThread::~ReplayThread ()
{

}
void ReplayThread::run ()
{
  captureRunning = true;
  while (captureRunning)
    {

    }
}

void ReplayThread::stop ()
{
  captureRunning = false;
}
