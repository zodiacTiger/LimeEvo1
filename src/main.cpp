#include "mainwindow.h"
#include <QSplashScreen>
#include <QLabel>
#include <QImage>
#include <QApplication>
#include <QElapsedTimer>
#include <QtWidgets>
#include <QGraphicsItemAnimation>
#include <Radios.h>
#include <RadioRtlSdr.hpp>
#include <RadioBladeRf.hpp>
#include "LimeDevice.h"
#include "helpers.hpp"

int main (int argc, char *argv[])
{
  QApplication a (argc, argv);
  MainWindow w;

  QSplashScreen *splash = new QSplashScreen;
  QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(splash);

  splash->setPixmap (QPixmap ("/Users/zero5/CLionProjects/LimeEvo1/images/splash.png"));
  splash->setGraphicsEffect(eff);

  QPropertyAnimation *splash_effect = new QPropertyAnimation(eff,"opacity");
  splash_effect->setDuration(1200);
  splash_effect->setStartValue(0);

  splash_effect->setEndValue(1);
  splash_effect->setEasingCurve(QEasingCurve::InBack);
  splash_effect->start(QPropertyAnimation::DeleteWhenStopped);
  QFont splashFont;
  splashFont.setFamily (QString::fromUtf8 ("UbuntuMono NF"));
  splashFont.setPointSize (12);

  Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
  splash->setFont (splashFont);
  int status = 0;
  splash->showMessage (QObject::tr ("Finding Device"),
                       topRight, Qt::white);
  if (LimeDevice::deviceFound ())
    {
    splash->showMessage (QObject::tr ("Lime Device Found"),
                         topRight, Qt::white);
    }
  else if (!LimeDevice::deviceFound ())
    {
    splash->showMessage (QObject::tr ("No Lime Device Found!"),
                         topRight, Qt::white);
    }
  splash->show ();

//  wait (2);

  delete splash;

  w.show ();
  return a.exec ();
}
