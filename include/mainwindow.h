#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGlobal>
#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "RxThread.hpp"
#include "TxThread.hpp"
#include "RadioBladeRf.hpp"

#define GUI_UPDATE_INTERVAL_MS 1

#define RX_START_GAIN 70
#define RX_START_FREQ 1938800000
#define RX_SAMPLE_RATE 2e6
#define RX_START_STREAM_RATE 0.5
#define RX_TO_FILE false
#define RX_CHANNEL 0
#define RX_ANTENNA LMS_PATH_LNAW

#define TX_START_GAIN 70
#define TX_START_FREQ 1938800000
#define TX_SAMPLE_RATE 2e6
#define TX_START_STREAM_RATE 0.3
#define TX_TO_FILE true
#define TX_CHANNEL 0
#define TX_ANTENNA LMS_PATH_TX1

QT_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui
{
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow (QWidget *parent = nullptr);
  ~MainWindow ();
  bool checkStream = false;
  Ui::MainWindow *ui;
  QMutex mutex;
  Rx::RxThread *rx = new Rx::RxThread (&mutex,RX_START_FREQ, RX_START_GAIN, RX_SAMPLE_RATE, RX_START_STREAM_RATE, RX_CHANNEL, RX_ANTENNA, RX_TO_FILE);
  Tx::TxThread *tx = new Tx::TxThread(TX_START_FREQ,TX_START_GAIN,TX_SAMPLE_RATE,TX_START_STREAM_RATE,TX_CHANNEL);
  QwtPlotCurve curveRX1;
  bool PlotAutoscaleEnabled = false;
 public slots:
  void updateSampleRX(float samples);

 private:
  QString rx_0_antenna = "";
  QString rx_1_antenna = "";
  QString tx_0_antenna = "";
  QString tx_1_antenna = "";
  QTimer *guiUpdate;

  double QwtPlotDefaultBottomMin = -.05;
  double QwtPlotDefaultLeftMin = -.05;
  double QwtPlotDefaultBottomMax = .05;
  double QwtPlotDefaultLeftMax = .05;

  void CheckDeviceConnection ();
  void CheckBoardTemp();
  void showStreamingStatus();
  void showBusyStatus();
  void showConnectedStatus();
  void showNoDeviceStatus();
  void showStoppingThreadStatus();
  void showThreadStoppedStatus();
  void increasePlotScale(int amount);
  void decreasePlotScale(int amount);
  void toggleQwtPlotAutoscale();

 private slots:
  void on_device_info_clicked ();
  void on_exit_clicked ();
  void on_rx_0_stream_clicked ();
  void on_rxtx_stop_clicked();
  void on_tx_0_stream_clicked ();
  void on_tx_test_sine_clicked ();
  void on_load_cfg_clicked ();
  void on_board_temp_clicked ();
  void on_stream_latency_changed();
  void on_stream_sample_rate_changed();
  void on_set_register_clicked();


  void on_center_freq_changed();
  void on_rx0_freq_up_clicked();

  void on_qwt_plot_scale_increase();
  void on_qwt_plot_scale_decrease();
  void on_qwt_plot_autoscale_clicked();

  void on_rx0_freq_down_clicked();
  void on_center_freq_line_edit();
  void on_gain_changed();
  void on_rx_0_antenna_changed();
  void on_rx_1_antenna_changed();
  void on_tx_1_gain_changed();
  void on_tx_1_freq_changed();
  void on_rxToFile_clicked();
  void on_gsmFreq1_clicked();
  void updateStreamStats();
  void on_bladerf_clicked();
 signals:
  void device_info_callback ();
  void rx_stream_callback ();
  void tx_stream_callback ();
  void test_sine_callback ();
  void load_cfg_callback ();
  void freq_updated();

};

#endif // MAINWINDOW_H
