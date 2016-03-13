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



void MainWindow::on_controlButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_configButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    ui->doubleSpinBox->setValue(value);
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    ui->doubleSpinBox_2->setValue(value);
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    ui->doubleSpinBox_3->setValue(value);
}


void MainWindow::on_actionMetric_triggered()
{
    ui->label_2->setText("rad/sec");
    ui->label_4->setText("rad/sec^2");
    ui->label_6->setText("rad/sec^3");
}

void MainWindow::on_actionEmperial_triggered()
{
    ui->label_2->setText("deg/sec");
    ui->label_4->setText("deg/sec^2");
    ui->label_6->setText("deg/sec^3");
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    ui->verticalSlider->setValue(arg1);
}
