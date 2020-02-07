#ifndef LIMEDEVICE_H
#define LIMEDEVICE_H

#include <QObject>
#include <QDebug>
#include <QPlainTextEdit>
#include <QWidget>
#include <QLabel>
#include "LimeRadio.hpp"

class LimeDevice : public QWidget {
 Q_OBJECT

 public:
  LimeDevice ();
  ~LimeDevice ();

  static bool deviceFound ();
  static int lms_device_error(lms_device_t *d);


 public slots:
  std::string boardTemp ();

 private slots:
  void on_device_info_clicked ();
//  std::string on_rx_stream_clicked();
  void on_tx_stream_clicked ();
  void on_tx_test_sine_clicked ();
  void on_load_cfg_clicked ();
  void on_exit_clicked ();
  void emit_test ();
  void receiveFromQML ();
  void on_gui_buttons_enabled ();

 signals:
  void sendToQML ();

 protected:
  int m_testProperty{};

};

#endif // LIMEDEVICE_H
