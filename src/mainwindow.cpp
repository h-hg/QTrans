#include "mainwindow.h"

#include <QUrlQuery>

#include "translator/googletranslator.h"
#include "translator/youdaotranslator.h"
#include "ui_mainwindow.h"
#include "utils/formatter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  trans = new YoudaoTranslator(this);
  // trans = new GoogleTranslator(this);
  connect(trans, &Translator::finished, this, &MainWindow::set_result_text);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  // ui->textEdit->setText(Formatter::removeLineBreaks(ui->plainTextEdit->toPlainText()));
  trans->translate(ui->plainTextEdit->toPlainText(),
                   Translator::SimplifiedChinese, Translator::English);
}

void MainWindow::set_result_text(QString content) {
  ui->textEdit->setText(content);
}
