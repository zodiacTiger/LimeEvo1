#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  MainWindow (QWidget *parent = nullptr);
  ~MainWindow ();

 private:
  Ui::MainWindow *ui;

 private slots:
  void on_device_info_clicked ();
  void on_exit_clicked ();
  void on_rx_stream_clicked ();
  void on_tx_stream_clicked ();
  void on_tx_test_sine_clicked ();
  void on_load_cfg_clicked ();
  void on_board_temp_clicked ();

 signals:
  void device_info_callback ();
  void rx_stream_callback ();
  void tx_stream_callback ();
  void test_sine_callback ();
  void load_cfg_callback ();

};

#endif // MAINWINDOW_H
