//
// Created by ZodiacTiger on 1/27/20.
//

#ifndef LIMEEVO1_DEVICEBRIDGE_HPP
#define LIMEEVO1_DEVICEBRIDGE_HPP

#include <QQuickItem>
#include <QObject>

class DeviceBridge : public QQuickItem {

 Q_OBJECT

  Q_PROPERTY(bool deviceGUIEnabled
                 READ
                 deviceGUIEnabled
                 WRITE
                 setDeviceGUIEnabledProperty
                 NOTIFY
                 deviceGUIEnabledPropertyChanged)

 public:
  explicit DeviceBridge (QQuickItem *parent = nullptr) : QQuickItem (parent), device_gui_enabled (true)
  {}
  ~DeviceBridge ();

  bool deviceGUIEnabled () const
  {
    qDebug () << "GUI eanbleadfadsf " << device_gui_enabled;
    return device_gui_enabled;
  }

 public slots:
  void setDeviceGUIEnabledProperty (bool deviceGUIEnabled)
  {
    device_gui_enabled = deviceGUIEnabled;
    emit deviceGUIEnabledPropertyChanged (device_gui_enabled);
  }

 signals:
  void deviceGUIEnabledPropertyChanged (bool enable);

 protected:
  bool device_gui_enabled;

};

#endif //LIMEEVO1_DEVICEBRIDGE_HPP
