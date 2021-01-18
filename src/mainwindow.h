#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "translator/onlinetranslator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();
  void set_result_text(QString);

 private:
  Ui::MainWindow *ui;
  OnlineTranslator *trans;
};
#endif  // MAINWINDOW_H
