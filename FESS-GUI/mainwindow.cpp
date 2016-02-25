#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_doubleSpinBox_valueChanged(const QString &arg1)
{
    ui->label->setText(arg1);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_2->setText(QString::number(value));
}

void MainWindow::on_dial_valueChanged(int value)
{
    ui->label_3->setText(QString::number(value));
}
