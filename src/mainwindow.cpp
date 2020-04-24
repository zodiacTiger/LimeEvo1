
#include <QWidget>
#include <lime/LimeSuite.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "LimeDevice.h"
#include "LimeRadio.hpp"
#include "RxThread.hpp"
#include "helpers.hpp"
#include "ReplayThread.hpp"
#include <QTimer>
#include <complex>
#include <Radios.h>
#include <RadioBladeRf.hpp>
#include <qwt_symbol.h>
#include <QKeyEvent>

double roundDecimal(double value, int precision )
{
  const int adjustment = pow(10,precision);
  return floor( value*(adjustment) + 0.5 )/adjustment;
}

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow)
{
  ui->setupUi (this);

  // Check for lime device
  MainWindow::CheckDeviceConnection ();

  // send initial data to GUI
  ui->connectedDevice->setText (LimeRadio::QTShowConnectedDevice ());
  ui->sampleRateUpdate->setText (rx->getSampleRate ());
  ui->gainUpdate->setText (rx->getCurrentGain ());
  ui->rx0_freq->setValue (RX_START_FREQ);
  ui->freqUpdate->setText (QString::number(ui->rx0_freq->value ())+ " Hz");
  ui->FIFOPercentUpdate->setText ("--");
  ui->MainDeviceMenu->hide ();
  ui->constellation1->setFixedWidth (731);
  ui->constellation1->move (10,40);
  rx->setPlotUpdateType (1);
  if(LimeRadio::DeviceConnected ())
    {
    MainWindow::CheckDeviceConnection ();
    MainWindow::CheckBoardTemp ();
    }
  else{
    ui->deviceOutput->append (">> WARNING: No Device Connected.");
    }
  rx_0_antenna=rx->setAntenna (0,ui->antennaSelect->currentIndex ());
  rx_1_antenna=rx->setAntenna (1,ui->antennaSelect_2->currentIndex ());

  ui->rxToFile_checkbox->setChecked (false);

  ui->rx1_constellation_plot_label->move(10,2);
  ui->constellation1->move (10,40);
  ui->constellation1->setAxisTitle (QwtPlot::xBottom,"Real (In Phase)");
  ui->constellation1->setAxisTitle (QwtPlot::yLeft,"Imaginary (Quadrature)");
  auto *sym = new QwtSymbol;

  curveRX1.setSymbol (sym);
  curveRX1.attach (ui->constellation1);
  curveRX1.setPen(QColor(QColor(168, 255, 79)),2,Qt::SolidLine);
  curveRX1.setStyle (QwtPlotCurve::Dots);
  QFont axisFont;
  axisFont.setPointSize (12);
  axisFont.setFamily(QString::fromUtf8("Exo2"));
  ui->constellation1->setAxisFont (QwtPlot::xBottom, axisFont);
  ui->constellation1->setAxisFont (QwtPlot::yLeft, axisFont);
  ui->constellation1->setFont (axisFont);
  ui->constellation1->setAxisAutoScale (QwtPlot::yLeft, false);
  ui->constellation1->setAxisAutoScale (QwtPlot::xBottom, false);
  ui->constellation1->setAxisScale (QwtPlot::xBottom,QwtPlotDefaultBottomMin,QwtPlotDefaultBottomMax);
  ui->constellation1->setAxisScale (QwtPlot::yLeft,QwtPlotDefaultLeftMin,QwtPlotDefaultLeftMax);


  ui->RXChannelLabel->setText (this->setCurrentChannel (ui->freqGainSettings->currentIndex () + 1,false));
  ui->streamSectionChannelLabel->setText (this->setCurrentChannel (ui->freqGainSettings->currentIndex () + 1, false));
  ui->streamSectionLabel->setText (" - STREAM MENU");
  ui->constellationPlotLabel->setText (" - CONSTELLATION PLOT");
  ui->dataOutput2->setText ("No active streams.");

//  this->setFocusPolicy(Qt::StrongFocus);
//  this->installEventFilter (this);
  this->installEventFilter (this->ui->freqUpdate);
  // start GUI update timer
  guiUpdate = new QTimer(this);

  // connect signal & slot of GUI update timer
  connect(guiUpdate,SIGNAL(timeout()),this,SLOT(updateStreamStats ()));
  connect (rx, SIGNAL(update_constellation_plot_signal ()), this, SLOT(update_constellation_plot ()));


}

MainWindow::~MainWindow ()
{
  delete rx;
  delete tx;
  delete ui;
}

void MainWindow::updateStreamStats ()
{
  if(rx->isRunning ())
    {
    lms_stream_status_t streamStatus = rx->getStreamStatus ();
    ui->dataRateUpdate_2->setText (rx->getDataRate ());
    ui->OverrunsUpdate->setText (rx->getOverruns ());
    ui->DroppedPacketsUpdate->setText (rx->getDroppedPackets ());
    ui->linkRateUpdate->setText (rx->getLinkRate () + " Mb/s");


    ui->FIFOPercentUpdate->setText (QString::number (
        (roundDecimal (
            (float) (rx->getStreamStatus ().fifoFilledCount / (float) rx->getStreamStatus ().fifoSize) * 100, 0))) + "%");
//    ui->deviceOutput->append (rx->getRXSample ());

    if (timedPlotUpdate)
      {
      QVector<QPointF> points (sizeof (rx->buffer_f32));

      for (int i = 0; i < rx->samples; i++)
        {

        points[i] = QPointF (rx->buffer_f32[i].real (), rx->buffer_f32[i].imag ());
        }
      curveRX1.setSamples (points);
      ui->constellation1->replot ();
      points.clear ();
      }
    }
}

void MainWindow::on_device_info_clicked ()
{
  MainWindow::CheckDeviceConnection ();
  ui->connectedDevice->setText (LimeRadio::QTShowConnectedDevice ());
  ui->deviceOutput->append(LimeRadio::QTShowConnectedDevice ());
}

void MainWindow::on_rx_0_stream_clicked ()
{

  if(LimeRadio::DeviceConnected())
    {
    showConnectedStatus ();
    ui->rx0->setDisabled (true);
    ui->tx0->setDisabled (true);
//    ui->connectedDevice->setText (LimeRadio::QTShowConnectedDevice ());
    ui->deviceOutput->append ("[LIME] RX Stream in progress.");
    rx->start (Rx::RxThread::HighestPriority);
//    ui->dataOutput2->setText ("Starting RX Stream");
    rx->moveToThread (rx);
    ui->stopRXStream->setText ("STOP STREAM");
    guiUpdate->start (ui->refreshRate->currentText ().toInt ());
      qDebug()<<"Update Stream Stats";
    ui->stopRXStream->setStyleSheet("QPushButton { \n"
                                    "\tbackground-color: rgb(56, 57, 56);\n"
                                    "color:  rgb(170, 255, 155);\n"
                                    "border-color: rgb(170, 255, 155);\n"
                                    "color: white;\n"
                                    "width: 90%;\n"
                                    "padding: 0;\n"
                                    "}\n"
                                    "\n"
                                    "QPushButton::hover {\n"
                                    "\tbackground-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(86, 86, 86, 255), stop:1 rgba(34, 35, 34, 255));\n"
                                    "border: 1px solid rgb(135, 135, 135);\n"
                                    "\n"
                                    "\tbackground-color: rgb(56, 57, 56);\n"
                                    "color:  rgb(170, 255, 155);\n"
                                    "border-color: rgb(170, 255, 155);\n"
                                    "}");
    if(rx->isRunning ())
      {
      ui->dataOutput2->setText ("RX Stream Active");

      }
    }
    else if( !checkStream && LimeRadio::DeviceConnected ())
    {

    if (rx->isRunning ())
      {
      MainWindow::showStreamingStatus ();
      }
    else
      {
      MainWindow::showConnectedStatus ();
        ui->rx0->setEnabled (true);
        ui->tx0->setEnabled (true);
      }
    }
    else if(!LimeRadio::DeviceConnected ())
    {
    ui->deviceOutput->append (">> RX FAILED: No Device Connected.");
    }

}
void MainWindow::on_tx_0_stream_clicked ()
{
  if(LimeRadio::DeviceConnected ())
    {
    ui->deviceOutput->append (">> Starting TX Stream");
    if(LimeRadio::DeviceConnected())
      {
      ui->rx0->setEnabled (false);
      ui->tx0->setEnabled (false);
      ui->deviceOutput->append(">> Device Found.");
      tx->start (QThread::HighestPriority);
      tx->moveToThread (tx);
      if(tx->isRunning ())
        {
        MainWindow::showStreamingStatus ();
        ui->deviceOutput->append(">> Lime TX Stream Started.");
        ui->dataOutput2->setText ("Tx Stream Started.");
        }
      else{
        ui->deviceOutput->append (">> Lime TX Stream failed.");
        ui->dataOutput2->setText ("Tx Stream Failed.");
        ui->rx0->setEnabled (true);
        ui->tx0->setEnabled (true);
        }
      }
    }
  else if(!LimeRadio::DeviceConnected ())
    {
    ui->deviceOutput->append (">> TX FAILED: No Device Connected.");
    }

}

void MainWindow::on_rxtx_stop_clicked ()
{
  if (rx->isRunning ())
    {
    rx->disableStream ();
    ui->dataOutput2->setText ("Stopping RX Stream");
    ui->deviceOutput->append ("Stopping RX Stream");
    while (!rx->isFinished () && rx->isRunning ())
      {
      rx->stop ();
      guiUpdate->stop ();
      ui->dataRateUpdate_2->setText("0 Ms/s");
      MainWindow::showStoppingThreadStatus ();

      wait (1);

      if (!rx->isRunning ())
        {
        ui->stopRXStream->setStyleSheet ("QPushButton { \n"
                                         "\tbackground-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(86, 86, 86, 255), stop:1 rgba(34, 35, 34, 255));\n"
                                         "border: 1px solid rgb(135, 135, 135);\n"
                                         "border-radius: 4px;\n"
                                         "\n"
                                         "color: #f2f2f2;\n"
                                         "width: 90%;\n"
                                         "padding: 0;\n"
                                         "}\n"
                                         "\n"
                                         "QPushButton::hover {\n"
                                         "\tbackground-color: rgb(56, 57, 56);\n"
                                         "color:  rgb(170, 255, 155);\n"
                                         "border-color: rgb(170, 255, 155);\n"
                                         "}");
        ui->dataOutput2->setText ("Stream Stopped.");
        MainWindow::showThreadStoppedStatus ();
        wait (1);
        MainWindow::CheckDeviceConnection ();
        ui->dataOutput2->setText ("No active streams.");
        ui->rx0->setEnabled (true);
        ui->tx0->setEnabled (true);
        }

      }
    }
  else if (tx->isRunning ())
    {
    ui->deviceOutput->append ("Stopping TX Stream");
    ui->dataOutput2->setText ("Stopping TX Stream");
    tx->disableStream ();
    while (!tx->isFinished () && tx->isRunning ())
      {
      tx->stop ();
      guiUpdate->stop ();
      MainWindow::showStoppingThreadStatus ();

      wait (1);
      if (!tx->isRunning ())
        {
        ui->dataOutput2->setText ("Stream Stopped");
        ui->deviceOutput->setStyleSheet (""
                                         "border: 1px solid rgb(61, 189, 68);\n"
                                         "background-color: rgb(22, 22, 22);\n"
                                         "color: rgb(241, 246, 246);"
        );

        MainWindow::showThreadStoppedStatus ();
        wait (1);
        ui->dataOutput2->setText ("No Streams Active");
        MainWindow::CheckDeviceConnection ();
        ui->tx0->setEnabled (true);
        ui->rx0->setEnabled (true);
        }
      }
    }
      else
        {
        ui->rx0->setEnabled (true);
        ui->tx0->setEnabled (true);
        ui->dataOutput2->setText ("No Streams in progress");
        ui->deviceOutput->append (">>> No Streams in progress.");
        }
      }


void MainWindow::on_load_cfg_clicked ()
{
  qDebug () << "load config, yay!!";
  MainWindow::CheckDeviceConnection ();
  ui->connectedDevice->setText (LimeRadio::QTShowConnectedDevice ());
  ui->deviceOutput->append(LimeRadio::QTShowConnectedDevice ());
  ui->deviceOutput->append ("load cfg");
}

void MainWindow::on_rx_0_antenna_changed(){
    rx_0_antenna = rx->setAntenna (0,ui->antennaSelect->currentIndex ());
    ui->deviceOutput->append (">> LMS DEVICE - RX 0 Antenna set to " + rx_0_antenna);
}

void MainWindow::on_rx_1_antenna_changed(){
  rx_1_antenna = rx->setAntenna (1,ui->antennaSelect_2->currentIndex ());
  ui->deviceOutput->append (">> LMS DEVICE - RX 1 Antenna set to " + rx_1_antenna);
}


void MainWindow::on_rxToFile_clicked(){
  rx->setRXToFile (ui->rxToFile_checkbox->checkState ());
  bool currentState=ui->rxToFile_checkbox->checkState ();
  if(currentState)
    {
      toggleButtonStylePressed (ui->rxtofile_button,true);
      ui->deviceOutput->append(">> Rx Stream to file enabled.");
    ui->rxToFile_checkbox->setChecked (true);

    }
  else{
    toggleButtonStylePressed (ui->rxtofile_button,false);
    ui->deviceOutput->append(">> Rx Stream to file disabled.");
    ui->rxToFile_checkbox->setChecked (false);
    }
}

void MainWindow::on_rxToFile_button_clicked ()
{
  if(rxToFileButtonActive)
    {
      this->toggleButtonStylePressed (ui->rxtofile_button,true);
    rxToFileButtonActive = false;
    ui->deviceOutput->append(">> Rx Stream to file disabled.");

    }
  else
    {
      this->toggleButtonStylePressed (ui->rxtofile_button,false);
    ui->deviceOutput->append(">> Rx Stream to file enabled.");

    rxToFileButtonActive = true;
    }
  ui->rxToFile_checkbox->setChecked (rxToFileButtonActive);

}

void MainWindow::on_tx_test_sine_clicked ()
{
      ui->dataRateUpdate_2->setText (rx->getDataRate ());
      lms_stream_status_t stream_status = rx->getStreamStatus ();
      if(stream_status.active && rx->isRunning ())
        {
          ui->dataOutput2->setText("[ STREAM IN PROGRESS ]");
          ui->dataOutput2->setText ("Total Samples RX'd=" + rx->getTotalSamples ());
//          ui->dataOutput2->append("sample time stamp=" + QString::number (stream_status.timestamp));
          ui->dataOutput2->setText ("Data Rate =" + rx->getDataRate ());
          ui->dataOutput2->setText ("Link Rate =" + QString::number (stream_status.linkRate));
          ui->dataOutput2->setText ("Overruns/Underruns/Packets Dropped =[ " +
                                  QString::number (stream_status.overrun) + " , " +
                                  QString::number (stream_status.underrun) + " , " +
                                  QString::number (stream_status.droppedPackets) + " ]"
          );
          ui->dataOutput2->setText ("FIFO fill/size=" + QString::number (stream_status.fifoFilledCount)
                                        + " / " + QString::number (stream_status.fifoSize)
          );
        }
      else{
        ui->dataOutput2->setText(">> No active streams.");
      }
}

void MainWindow::on_gsmFreq1_clicked()
{
  rx->setFreq (RX_START_FREQ, 0, LMS_CH_RX);
  ui->freqUpdate->setText (QString::number (RX_START_FREQ));
  ui->rx0_freq->setValue (RX_START_FREQ);
}

void MainWindow::on_exit_clicked ()
{
  qDebug () << "Exiting...";
  exit (0);
}

void MainWindow::on_board_temp_clicked ()
{
  if(LimeRadio::DeviceConnected ())
    {
    MainWindow::CheckDeviceConnection ();
    MainWindow::CheckBoardTemp ();
    }
  else{
    showNoDeviceStatus ();
    ui->deviceOutput->append (">> WARNING: No Device Connected.");
  }
}

void MainWindow::on_tx_1_gain_changed ()
{
  tx->setGain (ui->tx1Gain->value (),0);
  ui->tx1GainUpdate->setText (tx->getGain () + " db");
}

void MainWindow::on_tx_1_freq_changed ()
{
  tx->setFreq (ui->tx1Freq->value (),0);
  ui->tx1FreqUpdate->setText (QString::number (ui->tx1Freq->value ()));
}

void MainWindow::on_center_freq_changed()
{
  rx->setFreq (ui->rx0_freq->value (), 0, LMS_CH_RX);
  ui->freqUpdate->setText (QString::number(ui->rx0_freq->value ()) + " Hz");
}

void MainWindow::on_rx0_freq_up_clicked(){
  const unsigned int freq_scale = 10000;
  rx->setFreq (ui->rx0_freq->value () + freq_scale,0,LMS_CH_RX);
  ui->rx0_freq->setValue (ui->rx0_freq->value () + freq_scale);
  ui->freqUpdate->setText (QString::number (ui->rx0_freq->value ())+ " Hz");

};
void MainWindow::on_rx0_freq_down_clicked(){
  const unsigned int freq_scale = 10000;
  rx->setFreq (ui->rx0_freq->value () - freq_scale,0,LMS_CH_RX);
  ui->rx0_freq->setValue (ui->rx0_freq->value () - freq_scale);
  ui->freqUpdate->setText (QString::number (ui->rx0_freq->value ())+ " Hz");
}

void MainWindow::on_center_freq_line_edit()
{
  if(ui->freqUpdate->text ().toDouble() > 2147483647)
    {
    rx->setFreq (2147483647, 0, LMS_CH_RX);
    ui->rx0_freq->setValue (2147483647);
    ui->deviceOutput->append (">> Frequency set to " + ui->freqUpdate->text() + " Hz");
    }
    else if(ui->freqUpdate->text ().toDouble() < 70000000){
    rx->setFreq (70000000, 0, LMS_CH_RX);
    ui->rx0_freq->setValue (70000000);
    ui->deviceOutput->append (">> Frequency set to " + ui->freqUpdate->text() + " Hz");
    }
    else{
    rx->setFreq (ui->freqUpdate->text ().toDouble (), 0, LMS_CH_RX);
    ui->deviceOutput->append (">> Frequency set to " + ui->freqUpdate->text() + " Hz");
    ui->rx0_freq->setValue (ui->freqUpdate->text ().toInt());
    qDebug()<<"YO FREQ OKAY";
    }

}

void MainWindow::on_rx0_gain_changed ()
{
  rx->setGain (ui->rx0_master_gain->value (),0);
  ui->deviceOutput->append (">> RX-1 Overall Gain set to " + QString::number(ui->rx0_master_gain->value ()));
  ui->gainUpdate->setText (QString::number (ui->rx0_master_gain->value ()));
  ui->rx0_master_gain_update->setText (QString::number (ui->rx0_master_gain->value ()));
}

void MainWindow::CheckBoardTemp()
{
  ui->connectedDevice->setText (LimeRadio::QTShowConnectedDevice ());

  auto *device = new LimeDevice ();
  std::string temp = device->boardTemp ();

  temp.erase (temp.find_last_not_of ('0') + 1, std::string::npos);
  std::cout << "Current Board Temp: " << temp;

  if(device->boardTemp () != "0")
    {
    ui->tempUpdateLabel->setText (QString::fromStdString (temp) + "°C");
    ui->deviceOutput->append (">> Current board temperature=" + QString::fromStdString (temp) + " c");
    }
  else{
    MainWindow::showBusyStatus ();
    ui->deviceOutput->append (">> Current Board Temperture: Device Busy or not found");
    }
  delete device;
}

void MainWindow::CheckDeviceConnection()
{
  if(LimeRadio::DeviceConnected())
    {
    MainWindow::showConnectedStatus ();
    }
  else if(rx->isRunning ()){
    MainWindow::showBusyStatus ();
    wait(2);
    MainWindow::showStreamingStatus ();
    }
  else{
    MainWindow::showNoDeviceStatus ();
  }

}

void MainWindow::showStreamingStatus()
{
  ui->DeviceIsConnected->setText (QString("STREAMING"));
  ui->DeviceIsConnected->setStyleSheet (""
                                        "\tbackground-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.220588 rgba(126, 200, 10, 255), stop:0.647059 rgba(163, 236, 8, 255));\n"
                                        "border: 1px solid rgb(103, 103, 103);\n"
                                        "border-radius: 4px;\n"
                                        "color: #333;\n"
                                        "width: 90%;\n"
                                        "padding: 0;"
  );
}

void MainWindow::showBusyStatus()
{
  ui->DeviceIsConnected->setText(QString("DEVICE BUSY"));
  ui->DeviceIsConnected->setStyleSheet (""
                                        "background-color: red;\n"
                                        "border: 1px solid red;\n"
                                        "color: white;\n");
}

void MainWindow::showConnectedStatus ()
{
  ui->DeviceIsConnected->setText (QString("CONNECTED"));
  ui->DeviceIsConnected->setStyleSheet ("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.220588 rgba(18, 138, 8, 255), stop:0.647059 rgba(25, 191, 25, 255));\n"

                                        "color: white;\n"
  );
}

void MainWindow::showStoppingThreadStatus ()
{
  ui->DeviceIsConnected->setText (QString("STOPPING STREAM"));
  ui->DeviceIsConnected->setStyleSheet ("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.220588 rgba(198, 221, 8, 255), stop:0.651961 rgba(238, 255, 10, 255));\n"
                                        "border: 1px solid yellow;\n"
                                        "color: #333;\n");
}

void MainWindow::showNoDeviceStatus ()
{
  ui->DeviceIsConnected->setText (QString("NO DEVICE"));
  ui->DeviceIsConnected->setStyleSheet (""
                                        "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.220588 rgba(132, 31, 19, 255), stop:0.647059 rgba(207, 0, 11, 255));\n"
                                        "color: white;\n");
}

void MainWindow::showThreadStoppedStatus ()
{
  ui->DeviceIsConnected->setText (QString("STREAM STOPPED"));
  ui->DeviceIsConnected->setStyleSheet (""
                                        "background-color: rgb(165, 255, 129);\n"
                                        "color: #333;"
  );
}
void MainWindow::on_bladerf_clicked ()
{
  Radios *radio;
  BladeRFRadio bladerf_session;
  radio=&bladerf_session;
  ui->deviceOutput->append (">> Configuring BladeRF");
  radio->setup ();
  BladeRFRadio::device_status d = bladerf_session.getDeviceStatus ();
  if(d.rx_0_enabled)
    {
      ui->deviceOutput->append (">> RX 0 Enabled.");
    }
  ui->deviceOutput->append (QString::number (d.rx_0_samplerate));
  ui->deviceOutput->append (QString::number (d.rx_0_freq));
  radio->close_device ();
}

void MainWindow::updateSampleRX (float samples)
{
  ui->deviceOutput->append (QString::number (samples));
}

void MainWindow::toggleQwtPlotAutoscale()
{
  if(PlotAutoscaleEnabled)
    {
    ui->constellation1->setAxisAutoScale (QwtPlot::yLeft, false);
    ui->constellation1->setAxisAutoScale (QwtPlot::xBottom, false);
    this->toggleButtonStylePressed (ui->IQPlotAutoscale,false);
    PlotAutoscaleEnabled = false;
    }
  else{
    ui->constellation1->setAxisAutoScale (QwtPlot::yLeft, true);
    ui->constellation1->setAxisAutoScale (QwtPlot::xBottom, true);
    this->toggleButtonStylePressed (ui->IQPlotAutoscale,true);
    PlotAutoscaleEnabled = true;
  }
}

void MainWindow::on_qwt_plot_scale_increase ()
{
  qDebug()<<"QWt Plot increase -> " << QwtPlotDefaultLeftMin << "," << QwtPlotDefaultLeftMax;
  ui->constellation1->setAxisScale (QwtPlot::xBottom,QwtPlotDefaultBottomMin *= 1.1,QwtPlotDefaultBottomMax*=1.1);
  ui->constellation1->setAxisScale (QwtPlot::yLeft,QwtPlotDefaultLeftMin *=1.1,QwtPlotDefaultLeftMax*=1.1);
}

void MainWindow::on_qwt_plot_scale_decrease ()
{
  qDebug()<<"QWt Plot decrease -> " << QwtPlotDefaultBottomMin << "," << QwtPlotDefaultLeftMax;
  ui->constellation1->setAxisScale (QwtPlot::xBottom,QwtPlotDefaultBottomMin /= 1.1,QwtPlotDefaultBottomMax /= 1.1);
  ui->constellation1->setAxisScale (QwtPlot::yLeft,QwtPlotDefaultLeftMin /= 1.1,QwtPlotDefaultLeftMax /= 1.1);
}

void MainWindow::on_qwt_plot_autoscale_clicked ()
{
  this->toggleQwtPlotAutoscale ();
}

void MainWindow::on_stream_sample_rate_changed ()
{
  qDebug()<<"Sample Rate Changed.";
  rx->setSampleRate (ui->sampleRateComboBox->currentText ().toDouble ());
  ui->sampleRateUpdate->setText (QString::number(ui->sampleRateComboBox->currentText ().toInt()) + " MS/S");
  ui->deviceOutput->append (">> Sample Rate Changed to " + ui->sampleRateComboBox->currentText () + " MS/S");
}
void MainWindow::on_stream_latency_changed ()
{
  qDebug()<<"Latency Changed.";
  rx->setStreamLatency (ui->streamRateVsLatencyComboBox->currentText ().toDouble ());
  ui->deviceOutput->append (">> Latency vs Throughput changed to " + ui->streamRateVsLatencyComboBox->currentText ());
}

void MainWindow::on_set_register_clicked ()
{
  qDebug()<<"Register Set Clicked.";
}
void MainWindow::on_stream_format_changed ()
{
  ui->deviceOutput->append ("Data stream format changed to " + ui->sampleFormatChooser->currentText ());
  rx->setSampleFormat (ui->sampleFormatChooser->currentIndex ());
}
void MainWindow::on_rx0_tia_changed ()
{
  rx->setTIAGain (0, ui->rx0_tia_gain->value ());
  ui->deviceOutput->append (">> RX-1 TIA Gain set to " + QString::number (ui->rx0_tia_gain->value ()));
  ui->rx0_tia_gain_update->setText (QString::number (ui->rx0_tia_gain->value ()));
}
void MainWindow::on_rx0_pga_changed ()
{
  rx->setPGAGain (0, ui->rx0_pga_gain->value ());
  ui->deviceOutput->append (">> RX-1 PGA Gain set to " + QString::number(ui->rx0_pga_gain->value ()));
  ui->rx0_pga_update->setText (QString::number (ui->rx0_pga_gain->value ()));
}
void MainWindow::on_rx0_lna_changed ()
{
  rx->setLNAGain (0, ui->rx0_lna_gain->value ());
  ui->deviceOutput->append (">> RX-1 LNA Gain set to " + QString::number (ui->rx0_lna_gain->value ()));
  ui->rx0_lna_gain_update->setText (QString::number (ui->rx0_lna_gain->value ()));
}
QWidget *MainWindow::getUI ()
{
  return this;
}
void MainWindow::on_main_menu_toggle_clicked ()
{
  if(bMainMenuActive)
    {
    ui->MainDeviceMenu->hide ();
    ui->constellation1->setFixedWidth (731);
    ui->rx1_constellation_plot_label->setFixedWidth (731);
    ui->rx1_constellation_plot_label->move(10,0);
    ui->constellation1->move (10,40);
    this->toggleButtonStylePressed (ui->mainMenuToggle,false);
    bMainMenuActive = false;
    ui->mainMenuToggle->setText ("e");

    }
  else{
    ui->MainDeviceMenu->show ();
    ui->constellation1->setFixedWidth (591);
    ui->rx1_constellation_plot_label->setFixedWidth (591);
    ui->rx1_constellation_plot_label->move(150,0);
    ui->constellation1->move (150,40);
    this->toggleButtonStylePressed (ui->mainMenuToggle,true);
    ui->mainMenuToggle->setText ("E");
    bMainMenuActive = true;
  }
}
void MainWindow::on_gain_pressed ()
{

}

void MainWindow::toggleButtonStylePressed (QWidget *element, bool pressed)
{
  if(pressed)
    {
    element->setStyleSheet (
        "QPushButton {\n"
        "\tborder-color: rgb(71, 71, 71);\n"
        "color #333;\n"
        "\tbackground-color: qlineargradient(spread:pad, x1:1, y1:0.58, x2:1, y2:0, stop:0 rgba(166, 255, 25, 255), stop:0.862745 rgba(98, 212, 48, 255));\n"
        "}\n"
        "\n"
        "QPushButton::hover {\n"
        "border-color: rgb(170, 255, 145);\n"
        "\tcolor: #333;\n"
        "\tbackground-color: qlineargradient(spread:pad, x1:1, y1:0.58, x2:1, y2:0, stop:0 rgba(166, 255, 25, 255), stop:0.862745 rgba(98, 212, 48, 255));\n"
        "\n"
        "}"
    );

    }
  else{
    element->setStyleSheet (
        "QPushButton {\n"
        "\tborder-color: rgb(71, 71, 71);\n"
        "\tcolor: rgb(168, 255, 79);\n"
        "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.176471 rgba(123, 123, 123, 255), stop:0.710784 rgba(84, 84, 84, 255));\n"
        "}\n"
        "\n"
        "QPushButton::hover {\n"
        "border-color: rgb(170, 255, 145);\n"
        "\tbackground-color: qlineargradient(spread:pad, x1:0.438, y1:0, x2:0.433498, y2:1, stop:0 rgba(0, 0, 0, 255), stop:0.79803 rgba(94, 94, 94, 255));\n"
        "\tcolor: rgb(168, 255, 79);\n"
        "}"
    );
  }
}

void MainWindow::on_rx_capture_clicked ()
{
  qDebug()<<"RX Capture Clicked";
  ui->deviceOutput->append ("RX Quick Capture NOW!");
  capture->start (QThread::HighestPriority);
  capture->moveToThread (capture);
}


void MainWindow::on_rx_replay_clicked ()
{
  if(capture->isRunning ())
    {
     qDebug()<<"Capture is running";
     ui->deviceOutput->append ("Capture is Running");
     capture->stop ();
     qDebug()<< "Capture Stopped.";
    ui->deviceOutput->append ("Capture Stopped");
    }
  else{
    ui->deviceOutput->append ("No Capture Process Running");

    qDebug()<< "No Capture in progress.";
    }
  ui->deviceOutput->append("RX Replay NOW!");
  qDebug()<<"RX Replay Clicked";
}
void MainWindow::update_constellation_plot ()
{
//  QVector<QPointF>points(sizeof(rx->buffer_i16));
  QVector<QPointF>points(sizeof(rx->buffer_f32));

  for(int i=0;i<rx->samples;i++)
    {

//    points[i] = QPointF(rx->buffer_i16[i].real (),rx->buffer_i16[i].imag ());
    points[i] = QPointF(rx->buffer_f32[i].real (),rx->buffer_f32[i].imag ());

    }
  curveRX1.setSamples (points);
  ui->constellation1->replot ();
  points.clear ();
}
void MainWindow::on_plot_update_mode_changed ()
{
  if(ui->TimedPlotUpdate->isChecked ())
    {
      timedPlotUpdate = true;
      rx->setPlotUpdateType (0);
    std::cout << "xPLOT UPDATE TRUEx";

    }
  else if(!ui->TimedPlotUpdate->isChecked ())
    {
      timedPlotUpdate = false;
      rx->setPlotUpdateType (1);
    std::cout << "xPLOT UPDATE FALSEx";

    }
}
bool MainWindow::eventFilter (QObject *obj, QEvent *event)
{
  {
    if (event->type () == QEvent::KeyPress)
      {
      //and here put your own logic!!
      QKeyEvent *key = static_cast<QKeyEvent *>(event);
      if((key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return))
        {
          qDebug()<<"Enter Key Pressed.";
          this->ui->deviceOutput->append ("ENTER");
        }
      return true;
      }
    else
      {
      // standard event processing
      return QObject::eventFilter (obj, event);
      }
  }
}
QString MainWindow::setCurrentChannel (size_t chan, bool isTX)
{
  QString currentChanelLabel;

  if(isTX)
    {
    tx_current_channel = chan;
    currentChanelLabel = "TX CHANNEL " + QString::number (tx_current_channel);
    }
  else{
    rx_current_channel = chan;
    currentChanelLabel = "RX CHANNEL " + QString::number (rx_current_channel);
    }
    return currentChanelLabel;
}
void MainWindow::on_freq_gain_channel_tab_changed ()
{
  if(ui->freqGainSettings->currentIndex () == 0)
    {
    ui->RXChannelLabel->setText (this->setCurrentChannel (1,false));
    ui->streamSectionChannelLabel->setText (this->setCurrentChannel (1, false));
    }
  else if(ui->freqGainSettings->currentIndex () == 1)
    {
    ui->RXChannelLabel->setText (this->setCurrentChannel (2, false));
    ui->streamSectionChannelLabel->setText (this->setCurrentChannel (2, false));
    }
  else if(ui->freqGainSettings->currentIndex () == 2)
    {
    ui->RXChannelLabel->setText (this->setCurrentChannel (1, true));
    ui->streamSectionChannelLabel->setText (this->setCurrentChannel (1, true));
    }
  else
    {
    ui->RXChannelLabel->setText (this->setCurrentChannel (2, true));
    ui->streamSectionChannelLabel->setText (this->setCurrentChannel (2, true));
  }
}



