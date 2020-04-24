//
// Created by ZodiacTiger on 4/22/20.
//

#ifndef LIMEEVO1_REPLAYTHREAD_HPP
#define LIMEEVO1_REPLAYTHREAD_HPP

#include <QObject>
#include <QThread>

 class ReplayThread : public QThread {

 public:
  ReplayThread();
  ~ReplayThread () override;
  void run();
  void stop();
  bool captureRunning = false;
};

#endif //LIMEEVO1_REPLAYTHREAD_HPP
