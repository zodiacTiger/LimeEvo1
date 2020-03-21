//
// Created by ZodiacTiger on 2/21/20.
//

#ifndef LIMEEVO1_UI_H
#define LIMEEVO1_UI_H
/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
 public:
  QWidget *centralwidget;
  QFrame *frame;
  QFrame *LimeLogo;
  QWidget *layoutWidget;
  QVBoxLayout *verticalLayout;
  QPushButton *deviceInfo;
  QPushButton *rx;
  QPushButton *tx;
  QPushButton *BoardTemp;
  QPushButton *stopRXStream;
  QPushButton *testSine;
  QPushButton *exit;
  QTextEdit *deviceOutput;
  QTextEdit *dataOutput2;
  QFrame *frame_2;
  QSlider *gain;
  QSlider *freq;
  QLabel *label_2;
  QLabel *label_4;
  QLabel *DeviceOutLabel;
  QLabel *DeviceIsConnected;
  QLabel *DeviceSettingsLabel;
  QLabel *label;
  QLabel *tempUpdateLabel;
  QTextEdit *connectedDevice;
  QLabel *sampleRateUpdate;
  QLabel *sampleRateLabel;
  QLabel *gainLabel;
  QLabel *gainUpdate;
  QLabel *dataRateLabel;
  QLabel *dataRateUpdate;
  QLabel *streamAmpLabel;
  QLabel *streamAmpUpdate;
  QLabel *freqLabel;
  QLabel *freqUpdate;
  QwtPlot *qwtPlot;
  QLabel *DeviceOutLabel_2;
  QStatusBar *statusbar;
  QButtonGroup *deviceButtons;

  void setupUi(QMainWindow *MainWindow)
  {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(1116, 733);
    QFont font;
    font.setFamily(QString::fromUtf8("Titillium Web"));
    font.setPointSize(24);
    MainWindow->setFont(font);
    MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 32, 32);\n"
                                                "\n"
                                                "QPushButton{\n"
                                                "background-color: rgb(67, 67, 67);\n"
                                                "border: 1px solid rgb(163, 236, 8);\n"
                                                "color: #f2f2f2;\n"
                                                "font: 14pt \"Titillium Web\";\n"
                                                "width: 90%;\n"
                                                "padding: 0;\n"
                                                "}"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    frame = new QFrame(centralwidget);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setGeometry(QRect(10, 10, 141, 691));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy);
    frame->setLayoutDirection(Qt::LeftToRight);
    frame->setStyleSheet(QString::fromUtf8("background-color: rgb(105, 105, 105);\n"
                                           "border: 1px solid rgb(169, 172, 172);\n"
                                           "border-radius: 4px;"));
    frame->setFrameShape(QFrame::NoFrame);
    frame->setFrameShadow(QFrame::Plain);
    LimeLogo = new QFrame(frame);
    LimeLogo->setObjectName(QString::fromUtf8("LimeLogo"));
    LimeLogo->setGeometry(QRect(0, 0, 141, 71));
    LimeLogo->setStyleSheet(QString::fromUtf8("image: url(:/Users/zero5/CLionProjects/LimeEvo1/images/limelogo.png);\n"
                                              "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0294118 rgba(0, 0, 0, 255), stop:0.77451 rgba(123, 123, 123, 255));\n"
                                              "padding: 0;\n"
                                              "padding-bottom: 10px;\n"
                                              "border-bottom: 5px solid;\n"
                                              "border-bottom-color: rgb(163, 236, 8);\n"
                                              "margin: 0;\n"
                                              ""));
    LimeLogo->setFrameShape(QFrame::StyledPanel);
    LimeLogo->setFrameShadow(QFrame::Raised);
    layoutWidget = new QWidget(frame);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(20, 90, 101, 301));
    verticalLayout = new QVBoxLayout(layoutWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    deviceInfo = new QPushButton(layoutWidget);
    deviceButtons = new QButtonGroup(MainWindow);
    deviceButtons->setObjectName(QString::fromUtf8("deviceButtons"));
    deviceButtons->addButton(deviceInfo);
    deviceInfo->setObjectName(QString::fromUtf8("deviceInfo"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(deviceInfo->sizePolicy().hasHeightForWidth());
    deviceInfo->setSizePolicy(sizePolicy1);
    deviceInfo->setMaximumSize(QSize(300, 16777215));
    deviceInfo->setBaseSize(QSize(300, 0));
    deviceInfo->setStyleSheet(QString::fromUtf8("QPushButton { \n"
                                                "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0294118 rgba(0, 0, 0, 255), stop:0.77451 rgba(123, 123, 123, 255));\n"
                                                "border: 1px solid rgb(26, 26, 26);\n"
                                                "border-radius: 4px;\n"
                                                "\n"
                                                "color: #f2f2f2;\n"
                                                "	font: 25 13pt \"Titillium Web\";\n"
                                                "width: 90%;\n"
                                                "padding: 0;\n"
                                                "}\n"
                                                "\n"
                                                "QPushButton::hover {\n"
                                                "	background-color: rgb(56, 57, 56);\n"
                                                "color: rgb(163, 236, 8);\n"
                                                "border-color: rgb(179, 182, 182);\n"
                                                "}\n"
                                                ""));

    verticalLayout->addWidget(deviceInfo);

    rx = new QPushButton(layoutWidget);
    deviceButtons->addButton(rx);
    rx->setObjectName(QString::fromUtf8("rx"));
    sizePolicy1.setHeightForWidth(rx->sizePolicy().hasHeightForWidth());
    rx->setSizePolicy(sizePolicy1);
    rx->setMaximumSize(QSize(300, 16777215));
    rx->setBaseSize(QSize(300, 0));
    rx->setStyleSheet(QString::fromUtf8("QPushButton { \n"
                                        "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0294118 rgba(0, 0, 0, 255), stop:0.77451 rgba(123, 123, 123, 255));\n"
                                        "border: 1px solid rgb(26, 26, 26);\n"
                                        "border-radius: 4px;\n"
                                        "\n"
                                        "color: #f2f2f2;\n"
                                        "	font: 25 13pt \"Titillium Web\";\n"
                                        "width: 90%;\n"
                                        "padding: 0;\n"
                                        "}\n"
                                        "\n"
                                        "QPushButton::hover {\n"
                                        "	background-color: rgb(56, 57, 56);\n"
                                        "color: rgb(163, 236, 8);\n"
                                        "border-color: rgb(179, 182, 182);\n"
                                        "}\n"
                                        ""));

    verticalLayout->addWidget(rx);

    tx = new QPushButton(layoutWidget);
    deviceButtons->addButton(tx);
    tx->setObjectName(QString::fromUtf8("tx"));
    sizePolicy1.setHeightForWidth(tx->sizePolicy().hasHeightForWidth());
    tx->setSizePolicy(sizePolicy1);
    tx->setMaximumSize(QSize(300, 16777215));
    tx->setBaseSize(QSize(300, 0));
    tx->setStyleSheet(QString::fromUtf8("QPushButton { \n"
                                        "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0294118 rgba(0, 0, 0, 255), stop:0.77451 rgba(123, 123, 123, 255));\n"
                                        "border: 1px solid rgb(26, 26, 26);\n"
                                        "border-radius: 4px;\n"
                                        "\n"
                                        "color: #f2f2f2;\n"
                                        "	font: 25 13pt \"Titillium Web\";\n"
                                        "width: 90%;\n"
                                        "padding: 0;\n"
                                        "}\n"
                                        "\n"
                                        "QPushButton::hover {\n"
                                        "	background-color: rgb(56, 57, 56);\n"
                                        "color: rgb(163, 236, 8);\n"
                                        "border-color: rgb(179, 182, 182);\n"
                                        "}\n"
                                        ""));

    verticalLayout->addWidget(tx);

    BoardTemp = new QPushButton(layoutWidget);
    deviceButtons->addButton(BoardTemp);
    BoardTemp->setObjectName(QString::fromUtf8("BoardTemp"));
    sizePolicy1.setHeightForWidth(BoardTemp->sizePolicy().hasHeightForWidth());
    BoardTemp->setSizePolicy(sizePolicy1);
    BoardTemp->setMaximumSize(QSize(300, 16777215));
    BoardTemp->setBaseSize(QSize(300, 0));
    BoardTemp->setStyleSheet(QString::fromUtf8("QPushButton { \n"
                                               "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0294118 rgba(0, 0, 0, 255), stop:0.77451 rgba(123, 123, 123, 255));\n"
                                               "border: 1px solid rgb(26, 26, 26);\n"
                                               "border-radius: 4px;\n"
                                               "\n"
                                               "color: #f2f2f2;\n"
                                               "	font: 25 13pt \"Titillium Web\";\n"
                                               "width: 90%;\n"
                                               "padding: 0;\n"
                                               "}\n"
                                               "\n"
                                               "QPushButton::hover {\n"
                                               "	background-color: rgb(56, 57, 56);\n"
                                               "color: rgb(163, 236, 8);\n"
                                               "border-color: rgb(179, 182, 182);\n"
                                               "}\n"
                                               ""));

    verticalLayout->addWidget(BoardTemp);

    stopRXStream = new QPushButton(layoutWidget);
    deviceButtons->addButton(stopRXStream);
    stopRXStream->setObjectName(QString::fromUtf8("stopRXStream"));
    sizePolicy1.setHeightForWidth(stopRXStream->sizePolicy().hasHeightForWidth());
    stopRXStream->setSizePolicy(sizePolicy1);
    stopRXStream->setMaximumSize(QSize(300, 16777215));
    stopRXStream->setBaseSize(QSize(300, 0));
    stopRXStream->setStyleSheet(QString::fromUtf8("QPushButton { \n"
                                                  "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0294118 rgba(0, 0, 0, 255), stop:0.77451 rgba(123, 123, 123, 255));\n"
                                                  "border: 1px solid rgb(26, 26, 26);\n"
                                                  "border-radius: 4px;\n"
                                                  "\n"
                                                  "color: #f2f2f2;\n"
                                                  "	font: 25 13pt \"Titillium Web\";\n"
                                                  "width: 90%;\n"
                                                  "padding: 0;\n"
                                                  "}\n"
                                                  "\n"
                                                  "QPushButton::hover {\n"
                                                  "	background-color: rgb(56, 57, 56);\n"
                                                  "color: rgb(163, 236, 8);\n"
                                                  "border-color: rgb(179, 182, 182);\n"
                                                  "}\n"
                                                  ""));

    verticalLayout->addWidget(stopRXStream);

    testSine = new QPushButton(layoutWidget);
    deviceButtons->addButton(testSine);
    testSine->setObjectName(QString::fromUtf8("testSine"));
    sizePolicy1.setHeightForWidth(testSine->sizePolicy().hasHeightForWidth());
    testSine->setSizePolicy(sizePolicy1);
    testSine->setMaximumSize(QSize(300, 16777215));
    testSine->setBaseSize(QSize(300, 0));
    testSine->setStyleSheet(QString::fromUtf8("QPushButton { \n"
                                              "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0294118 rgba(0, 0, 0, 255), stop:0.77451 rgba(123, 123, 123, 255));\n"
                                              "border: 1px solid rgb(26, 26, 26);\n"
                                              "border-radius: 4px;\n"
                                              "\n"
                                              "color: #f2f2f2;\n"
                                              "	font: 25 13pt \"Titillium Web\";\n"
                                              "width: 90%;\n"
                                              "padding: 0;\n"
                                              "}\n"
                                              "\n"
                                              "QPushButton::hover {\n"
                                              "	background-color: rgb(56, 57, 56);\n"
                                              "color: rgb(163, 236, 8);\n"
                                              "border-color: rgb(179, 182, 182);\n"
                                              "}\n"
                                              ""));

    verticalLayout->addWidget(testSine);

    exit = new QPushButton(layoutWidget);
    deviceButtons->addButton(exit);
    exit->setObjectName(QString::fromUtf8("exit"));
    sizePolicy1.setHeightForWidth(exit->sizePolicy().hasHeightForWidth());
    exit->setSizePolicy(sizePolicy1);
    exit->setMaximumSize(QSize(300, 16777215));
    exit->setBaseSize(QSize(300, 0));
    exit->setStyleSheet(QString::fromUtf8("QPushButton { \n"
                                          "background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0294118 rgba(0, 0, 0, 255), stop:0.77451 rgba(123, 123, 123, 255));\n"
                                          "border: 1px solid rgb(26, 26, 26);\n"
                                          "border-radius: 4px;\n"
                                          "\n"
                                          "color: #f2f2f2;\n"
                                          "	font: 25 13pt \"Titillium Web\";\n"
                                          "width: 90%;\n"
                                          "padding: 0;\n"
                                          "}\n"
                                          "\n"
                                          "QPushButton::hover {\n"
                                          "	background-color: rgb(56, 57, 56);\n"
                                          "color: rgb(163, 236, 8);\n"
                                          "border-color: rgb(179, 182, 182);\n"
                                          "}\n"
                                          ""));

    verticalLayout->addWidget(exit);

    deviceOutput = new QTextEdit(centralwidget);
    deviceOutput->setObjectName(QString::fromUtf8("deviceOutput"));
    deviceOutput->setGeometry(QRect(160, 470, 371, 231));
    QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Expanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(deviceOutput->sizePolicy().hasHeightForWidth());
    deviceOutput->setSizePolicy(sizePolicy2);
    QFont font1;
    font1.setFamily(QString::fromUtf8("Titillium Web"));
    font1.setPointSize(12);
    font1.setBold(false);
    font1.setItalic(false);
    font1.setWeight(50);
    font1.setKerning(false);
    font1.setStyleStrategy(QFont::PreferAntialias);
    deviceOutput->setFont(font1);
    deviceOutput->setStyleSheet(QString::fromUtf8("color: rgb(125, 255, 36);\n"
                                                  "background-color: rgb(0, 0, 0);\n"
                                                  "border: 1px solid;\n"
                                                  "border-color: rgb(77, 77, 77);\n"
                                                  "border-top-left-radius: 8px;\n"
                                                  "border-bottom-left-radius: 8px;\n"
                                                  "border-bottom-right-radius: 8px;"));
    deviceOutput->setReadOnly(true);
    dataOutput2 = new QTextEdit(centralwidget);
    dataOutput2->setObjectName(QString::fromUtf8("dataOutput2"));
    dataOutput2->setGeometry(QRect(540, 470, 251, 231));
    QFont font2;
    font2.setFamily(QString::fromUtf8("Titillium Web"));
    font2.setPointSize(12);
    dataOutput2->setFont(font2);
    dataOutput2->setStyleSheet(QString::fromUtf8("paddingt-top: 20px;\n"
                                                 "color: rgb(125, 255, 36);\n"
                                                 "background-color: rgb(0, 0, 0);\n"
                                                 "border: 1px solid rgb(77, 77, 77);\n"
                                                 "border-top-right-radius: 8px;\n"
                                                 "border-bottom-left-radius: 8px;\n"
                                                 "border-bottom-right-radius: 8px;"));
    dataOutput2->setReadOnly(true);
    frame_2 = new QFrame(centralwidget);
    frame_2->setObjectName(QString::fromUtf8("frame_2"));
    frame_2->setGeometry(QRect(800, 470, 301, 231));
    frame_2->setStyleSheet(QString::fromUtf8("color: rgb(125, 255, 36);\n"
                                             "background-color: rgb(86, 86, 86);\n"
                                             "border: 1px solid rgb(153, 155, 155);\n"
                                             "border-top-right-radius: 8px;\n"
                                             "border-bottom-left-radius: 8px;\n"
                                             "border-bottom-right-radius: 8px;"));
    frame_2->setFrameShape(QFrame::StyledPanel);
    frame_2->setFrameShadow(QFrame::Raised);
    gain = new QSlider(frame_2);
    gain->setObjectName(QString::fromUtf8("gain"));
    gain->setGeometry(QRect(60, 40, 231, 21));
    gain->setStyleSheet(QString::fromUtf8("background-color: rgb(158, 158, 158);\n"
                                          "color: rgb(22, 23, 23);\n"
                                          "font: 25 13pt \"Titillium Web\";\n"
                                          "border-radius: 0;"));
    gain->setMinimum(1);
    gain->setMaximum(70);
    gain->setValue(40);
    gain->setOrientation(Qt::Horizontal);
    freq = new QSlider(frame_2);
    freq->setObjectName(QString::fromUtf8("freq"));
    freq->setGeometry(QRect(60, 70, 231, 20));
    freq->setStyleSheet(QString::fromUtf8("background-color: rgb(158, 158, 158);\n"
                                          "color: rgb(22, 23, 23);\n"
                                          "font: 25 13pt \"Titillium Web\";\n"
                                          "border-radius: 0;"));
    freq->setMinimum(70000000);
    freq->setMaximum(300000000);
    freq->setSingleStep(1000);
    freq->setValue(193880000);
    freq->setSliderPosition(193880000);
    freq->setOrientation(Qt::Horizontal);
    label_2 = new QLabel(frame_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 40, 41, 21));
    label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(54, 54, 54);\n"
                                             "color: rgb(95, 255, 47);\n"
                                             "font: 25 13pt \"Titillium Web\";\n"
                                             "border-radius: 0;\n"
                                             "border: 0;"));
    label_2->setAlignment(Qt::AlignCenter);
    label_4 = new QLabel(frame_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(10, 70, 41, 20));
    label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(54, 54, 54);\n"
                                             "color: rgb(95, 255, 47);\n"
                                             "font: 25 13pt \"Titillium Web\";\n"
                                             "border-radius: 0;\n"
                                             "border: 0;"));
    label_4->setAlignment(Qt::AlignCenter);
    DeviceOutLabel = new QLabel(centralwidget);
    DeviceOutLabel->setObjectName(QString::fromUtf8("DeviceOutLabel"));
    DeviceOutLabel->setGeometry(QRect(160, 450, 111, 20));
    DeviceOutLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(87, 200, 14);\n"
                                                    "color: rgb(28, 29, 29);\n"
                                                    "font: 25 13pt \"Titillium Web\";\n"
                                                    "border-top-left-radius: 6px;\n"
                                                    "border-top-right-radius: 6px;\n"
                                                    ""));
    DeviceOutLabel->setAlignment(Qt::AlignCenter);
    DeviceIsConnected = new QLabel(centralwidget);
    DeviceIsConnected->setObjectName(QString::fromUtf8("DeviceIsConnected"));
    DeviceIsConnected->setGeometry(QRect(970, 20, 111, 20));
    DeviceIsConnected->setStyleSheet(QString::fromUtf8("background-color: rgb(123, 123, 123);\n"
                                                       "color: rgb(28, 29, 29);\n"
                                                       "font: 25 13pt \"Titillium Web\";\n"
                                                       "border: 2px;\n"
                                                       "border-color: rgb(59, 255, 6);\n"
                                                       "border-radius: 8px;\n"
                                                       ""));
    DeviceIsConnected->setAlignment(Qt::AlignCenter);
    DeviceSettingsLabel = new QLabel(centralwidget);
    DeviceSettingsLabel->setObjectName(QString::fromUtf8("DeviceSettingsLabel"));
    DeviceSettingsLabel->setGeometry(QRect(800, 450, 121, 21));
    DeviceSettingsLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(87, 200, 14);\n"
                                                         "color: rgb(28, 29, 29);\n"
                                                         "font: 25 13pt \"Titillium Web\";\n"
                                                         "border-top-left-radius: 6px;\n"
                                                         "border-top-right-radius: 6px;\n"
                                                         ""));
    DeviceSettingsLabel->setAlignment(Qt::AlignCenter);
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(960, 10, 131, 91));
    QFont font3;
    font3.setFamily(QString::fromUtf8("Titillium Web"));
    font3.setPointSize(11);
    font3.setBold(false);
    font3.setItalic(false);
    font3.setWeight(50);
    label->setFont(font3);
    label->setStyleSheet(QString::fromUtf8("color: rgb(125, 255, 36);\n"
                                           "background-color: rgb(68, 68, 68);\n"
                                           "border: 1px solid rgb(153, 155, 155);\n"
                                           "border-radius: 8px;"));
    label->setAlignment(Qt::AlignCenter);
    tempUpdateLabel = new QLabel(centralwidget);
    tempUpdateLabel->setObjectName(QString::fromUtf8("tempUpdateLabel"));
    tempUpdateLabel->setGeometry(QRect(960, 70, 131, 31));
    tempUpdateLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(38, 39, 39);\n"
                                                     "border: 1px solid rgb(139, 141, 141);\n"
                                                     "border-radius: 8px;\n"
                                                     "border-top-left-radius: 0;\n"
                                                     "border-top-right-radius: 0;\n"
                                                     "color: rgb(111, 255, 7);\n"
                                                     "font: 27pt \"Titillium Web\";\n"
                                                     "text-align: center;"));
    tempUpdateLabel->setAlignment(Qt::AlignCenter);
    connectedDevice = new QTextEdit(centralwidget);
    connectedDevice->setObjectName(QString::fromUtf8("connectedDevice"));
    connectedDevice->setGeometry(QRect(160, 420, 781, 21));
    QFont font4;
    font4.setFamily(QString::fromUtf8("SF Mono"));
    font4.setPointSize(9);
    font4.setBold(false);
    font4.setItalic(false);
    font4.setWeight(50);
    font4.setStyleStrategy(QFont::PreferAntialias);
    connectedDevice->setFont(font4);
    connectedDevice->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid rgb(110, 111, 111);\n"
                                                     "border-top: 1px solid #f3f3f3;\n"
                                                     "background-color: rgb(22, 22, 22);\n"
                                                     "color: rgb(166, 166, 166);\n"
                                                     "border-left: 1px solid rgb(74, 193, 14);\n"
                                                     "border-right: 1px solid rgb(74, 193, 14);"));
    connectedDevice->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connectedDevice->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connectedDevice->setReadOnly(true);
    sampleRateUpdate = new QLabel(centralwidget);
    sampleRateUpdate->setObjectName(QString::fromUtf8("sampleRateUpdate"));
    sampleRateUpdate->setGeometry(QRect(950, 190, 151, 31));
    QFont font5;
    font5.setFamily(QString::fromUtf8("Titillium Web"));
    font5.setPointSize(21);
    font5.setBold(false);
    font5.setItalic(false);
    font5.setWeight(50);
    sampleRateUpdate->setFont(font5);
    sampleRateUpdate->setStyleSheet(QString::fromUtf8("background-color: rgb(38, 39, 39);\n"
                                                      "border: 1px solid rgb(139, 141, 141);\n"
                                                      "border-radius: 8px;\n"
                                                      "border-top-left-radius: 0;\n"
                                                      "border-top-right-radius: 0;\n"
                                                      "color: rgb(111, 255, 7);\n"
                                                      "font: 21pt \"Titillium Web\";\n"
                                                      "text-align: center;"));
    sampleRateUpdate->setAlignment(Qt::AlignCenter);
    sampleRateLabel = new QLabel(centralwidget);
    sampleRateLabel->setObjectName(QString::fromUtf8("sampleRateLabel"));
    sampleRateLabel->setGeometry(QRect(950, 170, 151, 21));
    sampleRateLabel->setFont(font3);
    sampleRateLabel->setStyleSheet(QString::fromUtf8("color: rgb(125, 255, 36);\n"
                                                     "background-color: rgb(68, 68, 68);\n"
                                                     "border: 1px solid rgb(153, 155, 155);\n"
                                                     "border-radius: 8px;\n"
                                                     "border-bottom-left-radius: 0;\n"
                                                     "border-bottom-right-radius: 0;"));
    sampleRateLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    gainLabel = new QLabel(centralwidget);
    gainLabel->setObjectName(QString::fromUtf8("gainLabel"));
    gainLabel->setGeometry(QRect(950, 230, 151, 21));
    gainLabel->setFont(font3);
    gainLabel->setStyleSheet(QString::fromUtf8("color: rgb(125, 255, 36);\n"
                                               "background-color: rgb(68, 68, 68);\n"
                                               "border: 1px solid rgb(153, 155, 155);\n"
                                               "border-radius: 8px;\n"
                                               "border-bottom-left-radius: 0;\n"
                                               "border-bottom-right-radius: 0;"));
    gainLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    gainUpdate = new QLabel(centralwidget);
    gainUpdate->setObjectName(QString::fromUtf8("gainUpdate"));
    gainUpdate->setGeometry(QRect(950, 250, 151, 31));
    gainUpdate->setFont(font5);
    gainUpdate->setStyleSheet(QString::fromUtf8("background-color: rgb(38, 39, 39);\n"
                                                "border: 1px solid rgb(139, 141, 141);\n"
                                                "border-radius: 8px;\n"
                                                "border-top-left-radius: 0;\n"
                                                "border-top-right-radius: 0;\n"
                                                "color: rgb(111, 255, 7);\n"
                                                "font: 21pt \"Titillium Web\";\n"
                                                "text-align: center;"));
    gainUpdate->setAlignment(Qt::AlignCenter);
    dataRateLabel = new QLabel(centralwidget);
    dataRateLabel->setObjectName(QString::fromUtf8("dataRateLabel"));
    dataRateLabel->setGeometry(QRect(950, 290, 151, 21));
    dataRateLabel->setFont(font3);
    dataRateLabel->setStyleSheet(QString::fromUtf8("color: rgb(125, 255, 36);\n"
                                                   "background-color: rgb(68, 68, 68);\n"
                                                   "border: 1px solid rgb(153, 155, 155);\n"
                                                   "border-radius: 8px;\n"
                                                   "border-bottom-left-radius: 0;\n"
                                                   "border-bottom-right-radius: 0;"));
    dataRateLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    dataRateUpdate = new QLabel(centralwidget);
    dataRateUpdate->setObjectName(QString::fromUtf8("dataRateUpdate"));
    dataRateUpdate->setGeometry(QRect(950, 310, 151, 31));
    dataRateUpdate->setFont(font5);
    dataRateUpdate->setStyleSheet(QString::fromUtf8("background-color: rgb(38, 39, 39);\n"
                                                    "border: 1px solid rgb(139, 141, 141);\n"
                                                    "border-radius: 8px;\n"
                                                    "border-top-left-radius: 0;\n"
                                                    "border-top-right-radius: 0;\n"
                                                    "color: rgb(111, 255, 7);\n"
                                                    "font: 21pt \"Titillium Web\";\n"
                                                    "text-align: center;"));
    dataRateUpdate->setAlignment(Qt::AlignCenter);
    streamAmpLabel = new QLabel(centralwidget);
    streamAmpLabel->setObjectName(QString::fromUtf8("streamAmpLabel"));
    streamAmpLabel->setGeometry(QRect(950, 350, 151, 21));
    streamAmpLabel->setFont(font3);
    streamAmpLabel->setStyleSheet(QString::fromUtf8("color: rgb(125, 255, 36);\n"
                                                    "background-color: rgb(68, 68, 68);\n"
                                                    "border: 1px solid rgb(153, 155, 155);\n"
                                                    "border-radius: 8px;\n"
                                                    "border-bottom-left-radius: 0;\n"
                                                    "border-bottom-right-radius: 0;"));
    streamAmpLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    streamAmpUpdate = new QLabel(centralwidget);
    streamAmpUpdate->setObjectName(QString::fromUtf8("streamAmpUpdate"));
    streamAmpUpdate->setGeometry(QRect(950, 370, 151, 31));
    streamAmpUpdate->setFont(font5);
    streamAmpUpdate->setStyleSheet(QString::fromUtf8("background-color: rgb(38, 39, 39);\n"
                                                     "border: 1px solid rgb(139, 141, 141);\n"
                                                     "border-radius: 8px;\n"
                                                     "border-top-left-radius: 0;\n"
                                                     "border-top-right-radius: 0;\n"
                                                     "color: rgb(111, 255, 7);\n"
                                                     "font: 21pt \"Titillium Web\";\n"
                                                     "text-align: center;"));
    streamAmpUpdate->setAlignment(Qt::AlignCenter);
    freqLabel = new QLabel(centralwidget);
    freqLabel->setObjectName(QString::fromUtf8("freqLabel"));
    freqLabel->setGeometry(QRect(950, 110, 151, 21));
    freqLabel->setFont(font3);
    freqLabel->setStyleSheet(QString::fromUtf8("color: rgb(125, 255, 36);\n"
                                               "background-color: rgb(68, 68, 68);\n"
                                               "border: 1px solid rgb(153, 155, 155);\n"
                                               "border-radius: 8px;\n"
                                               "border-bottom-left-radius: 0;\n"
                                               "border-bottom-right-radius: 0;"));
    freqLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    freqUpdate = new QLabel(centralwidget);
    freqUpdate->setObjectName(QString::fromUtf8("freqUpdate"));
    freqUpdate->setGeometry(QRect(950, 130, 151, 31));
    freqUpdate->setFont(font5);
    freqUpdate->setStyleSheet(QString::fromUtf8("background-color: rgb(38, 39, 39);\n"
                                                "border: 1px solid rgb(139, 141, 141);\n"
                                                "border-radius: 8px;\n"
                                                "border-top-left-radius: 0;\n"
                                                "border-top-right-radius: 0;\n"
                                                "color: rgb(111, 255, 7);\n"
                                                "font: 21pt \"Titillium Web\";\n"
                                                "text-align: center;"));
    freqUpdate->setAlignment(Qt::AlignCenter);
    qwtPlot = new QwtPlot(centralwidget);
    qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
    qwtPlot->setGeometry(QRect(169, 9, 771, 391));
    qwtPlot->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
    DeviceOutLabel_2 = new QLabel(centralwidget);
    DeviceOutLabel_2->setObjectName(QString::fromUtf8("DeviceOutLabel_2"));
    DeviceOutLabel_2->setGeometry(QRect(540, 450, 111, 20));
    DeviceOutLabel_2->setStyleSheet(QString::fromUtf8("background-color: rgb(87, 200, 14);\n"
                                                      "color: rgb(28, 29, 29);\n"
                                                      "font: 25 13pt \"Titillium Web\";\n"
                                                      "border-top-left-radius: 6px;\n"
                                                      "border-top-right-radius: 6px;\n"
                                                      ""));
    DeviceOutLabel_2->setAlignment(Qt::AlignCenter);
    MainWindow->setCentralWidget(centralwidget);
    label->raise();
    frame->raise();
    deviceOutput->raise();
    dataOutput2->raise();
    frame_2->raise();
    DeviceOutLabel->raise();
    DeviceIsConnected->raise();
    DeviceSettingsLabel->raise();
    tempUpdateLabel->raise();
    connectedDevice->raise();
    sampleRateLabel->raise();
    sampleRateUpdate->raise();
    gainLabel->raise();
    gainUpdate->raise();
    dataRateLabel->raise();
    dataRateUpdate->raise();
    streamAmpLabel->raise();
    streamAmpUpdate->raise();
    freqLabel->raise();
    freqUpdate->raise();
    qwtPlot->raise();
    DeviceOutLabel_2->raise();
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);
    QWidget::setTabOrder(deviceInfo, rx);
    QWidget::setTabOrder(rx, tx);
    QWidget::setTabOrder(tx, exit);
    QWidget::setTabOrder(exit, testSine);

    retranslateUi(MainWindow);
    QObject::connect(stopRXStream, SIGNAL(clicked()), MainWindow, SLOT(on_rx_stop_clicked()));
    QObject::connect(rx, SIGNAL(clicked()), MainWindow, SLOT(on_rx_stream_clicked()));
    QObject::connect(exit, SIGNAL(clicked()), MainWindow, SLOT(close()));
    QObject::connect(testSine, SIGNAL(clicked()), MainWindow, SLOT(on_tx_test_sine_clicked()));
    QObject::connect(deviceInfo, SIGNAL(clicked()), MainWindow, SLOT(on_device_info_clicked()));
    QObject::connect(tx, SIGNAL(clicked()), MainWindow, SLOT(on_tx_stream_clicked()));
    QObject::connect(BoardTemp, SIGNAL(clicked()), MainWindow, SLOT(on_board_temp_clicked()));
    QObject::connect(gain, SIGNAL(valueChanged(int)), MainWindow, SLOT(on_gain_changed()));
    QObject::connect(freq, SIGNAL(valueChanged(int)), MainWindow, SLOT(on_center_freq_changed()));

    QMetaObject::connectSlotsByName(MainWindow);
  } // setupUi

  void retranslateUi(QMainWindow *MainWindow)
  {
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    deviceInfo->setText(QCoreApplication::translate("MainWindow", "Device Info", nullptr));
    rx->setText(QCoreApplication::translate("MainWindow", "Rx", nullptr));
    tx->setText(QCoreApplication::translate("MainWindow", "Tx", nullptr));
    BoardTemp->setText(QCoreApplication::translate("MainWindow", "Board Temp", nullptr));
    stopRXStream->setText(QCoreApplication::translate("MainWindow", "Stop Stream", nullptr));
    testSine->setText(QCoreApplication::translate("MainWindow", "Check Stream", nullptr));
    exit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    deviceOutput->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                    "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                                                                    "p, li { white-space: pre-wrap; }\n"
                                                                    "</style></head><body style=\" font-family:'Titillium Web'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
                                                                    "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:8px; font-family:'UbuntuMono NF'; font-size:13pt;\"><br /></p></body></html>", nullptr));
    deviceOutput->setProperty("placeholderText", QVariant(QCoreApplication::translate("MainWindow", "Chose From Menu At Left", nullptr)));
    dataOutput2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                   "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                                                                   "p, li { white-space: pre-wrap; }\n"
                                                                   "</style></head><body style=\" font-family:'Titillium Web'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
                                                                   "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:8px; font-family:'UbuntuMono NF'; font-size:13pt;\"><br /></p></body></html>", nullptr));
    label_2->setText(QCoreApplication::translate("MainWindow", "Gain", nullptr));
    label_4->setText(QCoreApplication::translate("MainWindow", "Freq", nullptr));
    DeviceOutLabel->setText(QCoreApplication::translate("MainWindow", "Device Output", nullptr));
    DeviceIsConnected->setText(QCoreApplication::translate("MainWindow", "No Connection", nullptr));
    DeviceSettingsLabel->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    label->setText(QCoreApplication::translate("MainWindow", "Board Temp \302\272C", nullptr));
    tempUpdateLabel->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
    sampleRateUpdate->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
    sampleRateLabel->setText(QCoreApplication::translate("MainWindow", "Sample Rate", nullptr));
    gainLabel->setText(QCoreApplication::translate("MainWindow", "Gain", nullptr));
    gainUpdate->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
    dataRateLabel->setText(QCoreApplication::translate("MainWindow", "Data Rate", nullptr));
    dataRateUpdate->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
    streamAmpLabel->setText(QCoreApplication::translate("MainWindow", "Amplitude", nullptr));
    streamAmpUpdate->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
    freqLabel->setText(QCoreApplication::translate("MainWindow", "Center Frequency (Hz)", nullptr));
    freqUpdate->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
    DeviceOutLabel_2->setText(QCoreApplication::translate("MainWindow", "Stream Data", nullptr));
  } // retranslateUi

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#endif //LIMEEVO1_UI_H
