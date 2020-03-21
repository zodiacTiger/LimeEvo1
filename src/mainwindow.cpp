
#include <QWidget>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "LimeDevice.h"
#include "LimeRadio.hpp"
#include "RxThread.hpp"
#include "helpers.hpp"
#include <QTimer>
#include <complex>
#include <Radios.h>
#include <RadioBladeRf.hpp>
#include <qwt_symbol.h>



MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow)
{

  ui->setupUi (this);
  this->setFocusPolicy (Qt::StrongFocus);
  // Check for lime device
  MainWindow::CheckDeviceConnection ();

  // send initial data to GUI
  ui->connectedDevice->setText (LimeRadio::QTShowConnectedDevice ());
  ui->freqUpdate->setText (QString::number(ui->freq->value ()));
  ui->dataRateUpdate->setText ("--");
  ui->sampleRateUpdate->setText (rx->getSampleRate ());
  ui->gainUpdate->setText (rx->getCurrentGain () + " db");
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
//  ui->constellation1->setTitle ("RX 1");

  ui->constellation1->setAxisTitle (QwtPlot::xBottom,"Real (In Phase)");
  ui->constellation1->setAxisTitle (QwtPlot::yLeft,"Imaginary (Quadrature)");
  auto *sym = new QwtSymbol;
//  sym->setStyle (QwtSymbol::XCross);
  sym->setStyle (QwtSymbol::Rect);
  sym->setSize (3,3);
  sym->setPen(QColor(Qt::white),2);
  sym->setBrush (Qt::darkCyan);
//  curveRX1.setStyle (QwtPlotCurve::NoCurve);
  curveRX1.setSymbol (sym);
  curveRX1.attach (ui->constellation1);
//  curveRX1.setPen(QColor(Qt::white),2,Qt::SolidLine);
//  curveRX1.setBrush (Qt::darkCyan);

  ui->constellation1->setAxisAutoScale (QwtPlot::yLeft, false);
  ui->constellation1->setAxisAutoScale (QwtPlot::xBottom, false);

  ui->constellation1->setAxisScale (QwtPlot::xBottom,QwtPlotDefaultBottomMin,QwtPlotDefaultBottomMax);
  ui->constellation1->setAxisScale (QwtPlot::yLeft,QwtPlotDefaultLeftMin,QwtPlotDefaultLeftMax);

//  curveRX1.setStyle (QwtPlotCurve::Dots);
  ui->dataOutput2->setText ("No active streams.");

  // start GUI update timer
  guiUpdate = new QTimer(this);
  // connect signal & slot of GUI update timer
  connect(guiUpdate,SIGNAL(timeout()),this,SLOT(updateStreamStats ()));
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
    ui->dataRateUpdate->setText (rx->getDataRate ());
    ui->OverrunsUpdate->setText (rx->getOverruns ());
    ui->DroppedPacketsUpdate->setText (rx->getDroppedPackets ());
//    ui->FIFOupdate->setText (QString::number (streamStatus.fifoFilledCount) + " / " + QString::number (streamStatus.fifoSize));
//    ui->FIFOPercentUpdate->setText (QString::number((float)streamStatus.fifoFilledCount / (float)streamStatus.fifoSize * 100) + "%");
    ui->FIFOupdate->setText (QString::number (rx->getStreamStatus ().fifoFilledCount) + " / " + QString::number (rx->getStreamStatus ().fifoSize));
    ui->FIFOPercentUpdate->setText (QString::number(((float)rx->getStreamStatus ().fifoFilledCount/(float)rx->getStreamStatus ().fifoSize) * 100) + "%");
    ui->deviceOutput->append (rx->getRXSample ());

    QVector<QPointF>points(sizeof(Rx::RxThread::buffer));
    QVector<QPointF>points2(sizeof (rx->getRXSampleComplex ()));
    QVector<QPointF>points3(sizeof(std::complex<float>));
    for(int i=0;i<sizeof(points);i++)
      {
        points[i] = QPointF(rx->getRXSampleComplex ().real(),rx->getRXSampleComplex ().imag ());
      }
    curveRX1.setSamples (points);
    ui->constellation1->replot();
//    points.clear ();

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
    ui->deviceOutput->append ("[LIME] RX Stream in progress.");
    ui->rx0->setDisabled (true);
    ui->tx0->setDisabled (true);
    rx->start (Rx::RxThread::HighestPriority);
    ui->dataOutput2->setText ("Starting RX Stream");
    rx->moveToThread (rx);
    ui->dataOutput2->setText ("RX Stream Running.");
//    ui->dataOutput2->setStyleSheet ("color: #f2f2f2");
    guiUpdate->start (GUI_UPDATE_INTERVAL_MS);
    ui->connectedDevice->setText (LimeRadio::QTShowConnectedDevice ());
    MainWindow::showStreamingStatus ();
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
      ui->dataRateUpdate->setText ("0 Ms/s");
      MainWindow::showStoppingThreadStatus ();

      wait (1);

      if (!rx->isRunning ())
        {
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
  if(ui->rxToFile_checkbox->checkState ())
    {
    ui->deviceOutput->append(">> Rx Stream to file enabled.");
    }
  else{
    ui->deviceOutput->append(">> Rx Stream to file disabled.");
    }
}

void MainWindow::on_tx_test_sine_clicked ()
{
      ui->dataRateUpdate->setText (rx->getDataRate ());

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
  ui->freq->setValue (RX_START_FREQ);
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
  rx->setFreq (ui->freq->value (), 0, LMS_CH_RX);
  ui->freqUpdate->setText (QString::number(ui->freq->value ()));
}

void MainWindow::on_rx0_freq_up_clicked(){
  const unsigned int freq_scale = 10000;
  rx->setFreq (ui->freq->value () + freq_scale,0,LMS_CH_RX);
  ui->freq->setValue (ui->freq->value () + freq_scale);
  ui->freqUpdate->setText (QString::number (ui->freq->value ()));

};
void MainWindow::on_rx0_freq_down_clicked(){
  const unsigned int freq_scale = 10000;
  rx->setFreq (ui->freq->value () - freq_scale,0,LMS_CH_RX);
  ui->freq->setValue (ui->freq->value () - freq_scale);
  ui->freqUpdate->setText (QString::number (ui->freq->value ()));
}

void MainWindow::on_center_freq_line_edit()
{
  if(ui->freqUpdate->text ().toDouble() > 2147483647)
    {
    rx->setFreq (2147483647, 0, LMS_CH_RX);
    ui->freq->setValue (2147483647);
    ui->deviceOutput->append (">> Frequency set to " + ui->freqUpdate->text() + " Hz");
    }
    else if(ui->freqUpdate->text ().toDouble() < 70000000){
    rx->setFreq (70000000, 0, LMS_CH_RX);
    ui->freq->setValue (70000000);
    ui->deviceOutput->append (">> Frequency set to " + ui->freqUpdate->text() + " Hz");
    }
    else{
    rx->setFreq (ui->freqUpdate->text ().toDouble (), 0, LMS_CH_RX);
    ui->deviceOutput->append (">> Frequency set to " + ui->freqUpdate->text() + " Hz");
    ui->freq->setValue (ui->freqUpdate->text ().toInt());
    qDebug()<<"YO FREQ OKAY";
    }

}

void MainWindow::on_gain_changed ()
{
  rx->setGain (ui->gain->value (),0);
//  ui->deviceOutput->append (rx->setGain (ui->gain->value ()));
  ui->gainUpdate->setText (QString::number (ui->gain->value ())+ " dB");
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
    ui->tempUpdateLabel->setText (QString::fromStdString (temp));
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
                                        "font: 25 13pt \"Titillium Web\";\n"
  );
}

void MainWindow::showBusyStatus()
{
  ui->DeviceIsConnected->setText(QString("DEVICE BUSY"));
  ui->DeviceIsConnected->setStyleSheet (""
                                        "background-color: red;\n"
                                        "border: 1px solid red;\n"
                                        "color: white;\n"
                                        "font: 25 13pt \"Titillium Web\";\n");
}

void MainWindow::showConnectedStatus ()
{
  ui->DeviceIsConnected->setText (QString("CONNECTED"));
  ui->DeviceIsConnected->setStyleSheet ("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.220588 rgba(18, 138, 8, 255), stop:0.647059 rgba(25, 191, 25, 255));\n"

                                        "color: white;\n"
                                        "font: 25 13pt \"Titillium Web\";\n"
  );
}

void MainWindow::showStoppingThreadStatus ()
{
  ui->DeviceIsConnected->setText (QString("STOPPING STREAM"));
  ui->DeviceIsConnected->setStyleSheet ("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.220588 rgba(198, 221, 8, 255), stop:0.651961 rgba(238, 255, 10, 255));\n"
                                        "border: 1px solid yellow;\n"
                                        "color: #333;\n"
                                        "font: 25 13pt \"Titillium Web\";\n");
}

void MainWindow::showNoDeviceStatus ()
{
  ui->DeviceIsConnected->setText (QString("NO DEVICE"));
  ui->DeviceIsConnected->setStyleSheet (""
                                        "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.220588 rgba(132, 31, 19, 255), stop:0.647059 rgba(207, 0, 11, 255));\n"
                                        "color: white;\n"
                                        "font: 25 13pt \"Titillium Web\";\n");
}

void MainWindow::showThreadStoppedStatus ()
{
  ui->DeviceIsConnected->setText (QString("STREAM STOPPED"));
  ui->DeviceIsConnected->setStyleSheet (""
                                        "background-color: rgb(165, 255, 129);\n"
                                        "color: #333;"
                                        "font: 25 13pt \"Titillium Web\";\n"
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
    PlotAutoscaleEnabled = false;
    }
  else{
    ui->constellation1->setAxisAutoScale (QwtPlot::yLeft, true);
    ui->constellation1->setAxisAutoScale (QwtPlot::xBottom, true);
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
  ui->sampleRateUpdate->setText (QString::number(ui->sampleRateComboBox->currentText ().toDouble ()) + " MS");
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
