#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QTimer>
#include <qwidget.h>
#include "rtg.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RTG *mainGraph = new RTG(ui->maingraph, true);
    RTG *velGraph = new RTG(ui->auxgraph1, false);
    RTG *accGraph = new RTG(ui->auxgraph2, false);


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->maingraph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->maingraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->maingraph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->maingraph->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    QTimer *dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}
void MainWindow::addMainData(double key, double value0, double value1)
{
    ui->maingraph->graph(0)->addData(key, value0);
    ui->maingraph->graph(1)->addData(key, value1);
    // set data of dots:
    ui->maingraph->graph(2)->clearData();
    ui->maingraph->graph(2)->addData(key, value0);
    ui->maingraph->graph(3)->clearData();
    ui->maingraph->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->maingraph->graph(0)->removeDataBefore(key-8);
    ui->maingraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->maingraph->graph(0)->rescaleValueAxis();
    ui->maingraph->graph(1)->rescaleValueAxis(true);
}

void MainWindow::addAux1Data(double key, double value0, double value1)
{
    ui->auxgraph1->graph(0)->addData(key, value0);
    ui->auxgraph1->graph(1)->addData(key, value1);
    // set data of dots:
    ui->auxgraph1->graph(2)->clearData();
    ui->auxgraph1->graph(2)->addData(key, value0);
    ui->auxgraph1->graph(3)->clearData();
    ui->auxgraph1->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->auxgraph1->graph(0)->removeDataBefore(key-8);
    ui->auxgraph1->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxgraph1->graph(0)->rescaleValueAxis();
    ui->auxgraph1->graph(1)->rescaleValueAxis(true);
}

void MainWindow::addAux2Data(double key, double value0, double value1)
{
    ui->auxgraph2->graph(0)->addData(key, value0);
    ui->auxgraph2->graph(1)->addData(key, value1);
    // set data of dots:
    ui->auxgraph2->graph(2)->clearData();
    ui->auxgraph2->graph(2)->addData(key, value0);
    ui->auxgraph2->graph(3)->clearData();
    ui->auxgraph2->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->auxgraph2->graph(0)->removeDataBefore(key-8);
    ui->auxgraph2->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxgraph2->graph(0)->rescaleValueAxis();
    ui->auxgraph2->graph(1)->rescaleValueAxis(true);
}

void MainWindow::realtimeDataSlot()
{

    // calculate two new data points:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;

    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
      double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
      double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
      // add data to lines:
      addMainData(key, value0, value1);
      addAux1Data(key, value0, (double)ui->doubleSpinBox->value());
      addAux2Data(key, value0, (double)ui->doubleSpinBox_2->value());
      lastPointKey = key;

    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->maingraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->maingraph->replot();

    ui->auxgraph1->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxgraph1->replot();

    ui->auxgraph2->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxgraph2->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->maingraph->graph(0)->data()->count()+ui->maingraph->graph(1)->data()->count())
            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
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
