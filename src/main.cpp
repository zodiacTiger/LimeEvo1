#include <iostream>
#include <chrono>
#include <QApplication>
#include <QtWidgets>
#include <QPushButton>
#include "mainwindow.h"
#include <lime/LimeSuite.h>
#include "LimeRadio.hpp"

int main (int argc, char *argv[])
{
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
  QApplication app(argc,argv);
//  MainWindow::CustomSizeHintMap customSizeHints;
//  switch (parseCustomSizeHints(QCoreApplication::arguments(), &customSizeHints)) {
//    case CommandLineArgumentsOk:
//      break;
//    case CommandLineArgumentsError:
//      usage();
//      return -1;
//    case HelpRequested:
//      usage();
//      return 0;
//    }

MainWindow window;
//  QPropertyAnimation *animation = new QPropertyAnimation(ui->pushButton, "geometry");
//  animation->setDuration(10000);
//  animation->setStartValue(ui->pushButton->geometry());
//  animation->setEndValue(QRect(200, 200, 100, 50));
//  animation->start();

  QPushButton *button1 = new QPushButton("Sup",&window);
  button1->show ();
  window.resize (800,600);
  window.setWindowTitle ("TESTING");
  window.show ();
  lms_device_t *d = NULL;
  lms_info_str_t dlist[8];
  LimeRadio r;
  std::cout << r.status (0);
//  LimeRadio::find (d,dlist);
//  std::cout << r.status (0);
//  std::cout << r.status (1);
  return app.exec ();

}