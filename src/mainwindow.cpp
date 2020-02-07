
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "LimeDevice.h"
#include "LimeRadio.hpp"



MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow)
{
  ui->setupUi (this);
}

MainWindow::~MainWindow ()
{
  delete ui;
}

void MainWindow::on_device_info_clicked ()
{
  lms_info_str_t dxlist[8];
  lms_device_t *dx = NULL;
  qDebug () << "YAY";
  ui->deviceOutput->append (LimeRadio::QTStatus (0, dx, dxlist));
}

void MainWindow::on_rx_stream_clicked ()
{
  lms_device_t *d = nullptr;
  lms_info_str_t device_info_list[8];
  LMS_GetDeviceList (device_info_list);
  LMS_Open (&d, device_info_list[0], NULL);
  double freq = 1000000;
  double samp_rate = 8000000;
  double temp = 0;

  LMS_GetChipTemperature (d, 0, &temp);
  qDebug () << "\nLIME DEVICE :: Board Temperature" << temp << " C";


  if (LMS_Init (d))
    {
//      error (d);
    }
  else
    {
    std::cout << "Device Initialized\n";
    ui->deviceOutput->append ("Lime device initialized");
    }
  if (LMS_EnableChannel (d, LMS_CH_RX, 0, true) != 0)
    {
//      error(d);
    }
  else
    {
    std::cout << "Channel Configured\n";
    ui->deviceOutput->append ("Lime device configured");
    }
  if (LMS_SetLOFrequency (d, LMS_CH_RX, 0, freq) != 0)
    {
//      error(d);
    }
  else
    {
    std::cout << "Frequency set at " << freq << endl;
    ui->deviceOutput->append ("Frequency Configured at " + QString::number (freq) + " Hz");
    }
  if (LMS_SetSampleRate (d, samp_rate, 2) != 0)
    {
//    error(d);
    }

    //Channels are numbered starting at 0
  else
    {
    ui->deviceOutput->append ("Sample rate set at " + QString::number (samp_rate));
    }

  if (LMS_EnableChannel (d, LMS_CH_RX, 0, true) != 0)
    {
    //    error();

    }
  else
    {
    ui->deviceOutput->append ("RX Channel Enabled ");
    }
  if (LMS_SetTestSignal (d, LMS_CH_RX, 0, LMS_TESTSIG_NCODIV8, 0, 0) != 0)

    if (LMS_Reset (d) == 0)
      {
      qDebug () << "\nLIME DEVICE :: Reset ";
      }
  LMS_Close (d);

//  r->configureRX(dx,dxlist,0,8e6,100e6);

}
void MainWindow::on_tx_stream_clicked ()
{
  qDebug () << "tx stream yay!!";
  ui->deviceOutput->append ("tx stream yay!!");
}
void MainWindow::on_load_cfg_clicked ()
{
  qDebug () << "load config, yay!!";
  ui->deviceOutput->append ("load cfg");
}
void MainWindow::on_tx_test_sine_clicked ()
{
  qDebug () << "test sine, yay!!";
  ui->deviceOutput->append ("Test Sine, yay");
}

void MainWindow::on_exit_clicked ()
{
  qDebug () << "Exiting...";
  exit (0);
}
void MainWindow::on_board_temp_clicked ()
{
  LimeDevice *d = new LimeDevice ();
  int num = 0;
  std::string temp = d->boardTemp ();
  temp.erase (temp.find_last_not_of ('0') + 1, std::string::npos);
  std::cout << "Current Board Temp: " << temp;
  ui->tempUpdateLabel->setText (QString::fromStdString (temp));
  ui->deviceOutput->append ("Current Board Temperture: " + QString::fromStdString (temp) + " ºC");

}
