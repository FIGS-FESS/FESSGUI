#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< HEAD
#include "parametersettings.h"
#include "QKeyEvent"
=======
#include <QKeyEvent>

>>>>>>> refs/remotes/origin/master

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

    ui->spinBox->setValue(value);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
<<<<<<< HEAD
    if(event->key() == Qt::Key_Space
            && ui->tabWidget->currentIndex() == 3)
       QApplication::quit();
}
=======
    int x = ui->horizontalSlider->value();

    switch(event->key())
    {
    case Qt::Key_Space :
        if (ui->tabWidget->currentIndex() == 2)
            QApplication::quit();
        break;
>>>>>>> refs/remotes/origin/master

    case Qt::Key_Plus :
        if (ui->tabWidget->currentIndex() == 1)
            ui->horizontalSlider->setValue(++x);
        break;



    case Qt::Key_Minus :
        if (ui->tabWidget->currentIndex() == 1)
            ui->horizontalSlider->setValue(--x);
        break;

    default :
        break;
    }
}


void MainWindow::on_dial_valueChanged(int value)
{
    ui->horizontalSlider->setValue(value);
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->setText("Check out these tutorials:\n https://www.youtube.com/watch?v=CRVwBNkn63s");
}


<<<<<<< HEAD
void MainWindow::on_actionAdjust_Paramaters_triggered()
{
    ParameterSettings pSettings;
    pSettings.setModal(true);
    pSettings.exec();
=======
void MainWindow::on_spinBox_valueChanged(int value)
{
    ui->horizontalSlider->setValue(value);
>>>>>>> refs/remotes/origin/master
}
