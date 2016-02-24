#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parametersettings.h"
#include "QKeyEvent"

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


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QFont font = ui->label_2->font();
    font.setPointSize(value);

    ui->label_2->setFont(font);

    ui->dial->setValue(value);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space
            && ui->tabWidget->currentIndex() == 3)
       QApplication::quit();
}



void MainWindow::on_dial_valueChanged(int value)
{
    ui->horizontalSlider->setValue(value);
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->setText("Check out these tutorials:\n https://www.youtube.com/watch?v=CRVwBNkn63s");
}


void MainWindow::on_actionAdjust_Paramaters_triggered()
{
    ParameterSettings pSettings;
    pSettings.setModal(true);
    pSettings.exec();
}
