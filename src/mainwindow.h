//
// Created by ZodiacTiger on 1/16/20.
//

#ifndef LIMEEVO1_MAINWINDOW_H
#define LIMEEVO1_MAINWINDOW_H
#include <QtWidgets>
#include <QMainWindow>
namespace Ui {
class MainWindow;

}
class MainWindow : public QMainWindow
{
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
//  ~MainWindow();

 private:
  Ui::MainWindow *ui;

  void createActions();
  void createStatusBar();
  void readSettings();
  void writeSettings();
  bool maybeSave();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

// protected:
//  void closeEvent(QCloseEvent *event) override;

// private slots:
//      void newFile();
//      void open();
//      bool save();
//      bool saveAs();
//      void about();
//      void documentWasModified();
//    #ifndef QT_NO_SESSIONMANAGER
//      void commitData(QSessionManager &);
//    #endif


  QPlainTextEdit *textEdit;
  QString curFile;

};


#endif //LIMEEVO1_MAINWINDOW_H
