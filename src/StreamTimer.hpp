//
// Created by ZodiacTiger on 2/21/20.
//

#ifndef LIMEEVO1_STREAMTIMER_HPP
#define LIMEEVO1_STREAMTIMER_HPP
#include <QTimer>

class StreamTimer: public QObject {
 Q_OBJECT

 public:
  StreamTimer();
  QTimer *timer;
  static bool getUpdate();

 public slots:
  bool StreamTimerSlot();

};



#endif //LIMEEVO1_STREAMTIMER_HPP
