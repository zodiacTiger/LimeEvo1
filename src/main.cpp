#include "mainwindow.h"
#include <QSplashScreen>
#include <QLabel>
#include <QImage>
#include <QApplication>
#include <QElapsedTimer>
#include "LimeDevice.h"

void wait (float sec)
{
  QElapsedTimer timer;
  timer.start ();
  while (!timer.hasExpired (sec * 1000))
    QCoreApplication::processEvents ();
}

int main (int argc, char *argv[])
{
  QApplication a (argc, argv);
  MainWindow w;

  QSplashScreen *splash = new QSplashScreen;
  splash->setPixmap (QPixmap ("/Users/zero5/CLionProjects/LimeEvo1/images/splash.png"));
  splash->show ();
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

  wait (1);

  delete splash;

  w.show ();
  return a.exec ();
}
