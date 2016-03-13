#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QTimer>
#include <qwidget.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->widget->addGraph(); // blue line
    ui->widget->graph(0)->setPen(QPen(Qt::blue));
    ui->widget->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->widget->graph(0)->setAntialiasedFill(false);
    ui->widget->addGraph(); // red line
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    ui->widget->graph(0)->setChannelFillGraph(ui->widget->graph(1));

    ui->widget->addGraph(); // blue dot
    ui->widget->graph(2)->setPen(QPen(Qt::blue));
    ui->widget->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->widget->addGraph(); // red dot
    ui->widget->graph(3)->setPen(QPen(Qt::red));
    ui->widget->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->widget->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->widget->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->widget->xAxis->setAutoTickStep(false);
    ui->widget->xAxis->setTickStep(2);
    ui->widget->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    QTimer *dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
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
      ui->widget->graph(0)->addData(key, value0);
      ui->widget->graph(1)->addData(key, value1);
      // set data of dots:
      ui->widget->graph(2)->clearData();
      ui->widget->graph(2)->addData(key, value0);
      ui->widget->graph(3)->clearData();
      ui->widget->graph(3)->addData(key, value1);
      // remove data of lines that's outside visible range:
      ui->widget->graph(0)->removeDataBefore(key-8);
      ui->widget->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      ui->widget->graph(0)->rescaleValueAxis();
      ui->widget->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->widget->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->widget->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->widget->graph(0)->data()->count()+ui->widget->graph(1)->data()->count())
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
