#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QTime>
#include <qwidget.h>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    goplayer = new QMediaPlayer(); //sound players
    stopplayer = new QMediaPlayer();
    playSounds = false;
    mainGraphDisplay = VEL; //enum for maingraph
    maxVel = 0;
    maxAcc = 0;

    ui->label_10->setStyleSheet("QLabel {color : blue; }"); //legend
    ui->label_11->setStyleSheet("QLabel {color : red; }");

    mainGraph = new RTG(ui->maingraph, true);  //initialize graphs
    velGraph = new RTG(ui->auxVelocGraph, false);
    accGraph = new RTG(ui->auxAccelGraph, false);
    updtGraph = new RTG(ui->auxUpDtGraph, false);
    lowdtGraph = new RTG(ui->auxLowDtGraph, false);
    rotatGraph = new RTG(ui->auxRotatGraph, false);


    free (mainGraph); //free classes
    free (velGraph);
    free (accGraph);
    free (updtGraph);
    free (lowdtGraph);
    free (rotatGraph);


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->maingraph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->maingraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->maingraph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->maingraph->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    dataTimer = new QTimer(this);
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

void MainWindow::addVelocData(double key, double value0, double value1)
{
    ui->auxVelocGraph->graph(0)->addData(key, value0);
    ui->auxVelocGraph->graph(1)->addData(key, value1);
    // set data of dots:
    ui->auxVelocGraph->graph(2)->clearData();
    ui->auxVelocGraph->graph(2)->addData(key, value0);
    ui->auxVelocGraph->graph(3)->clearData();
    ui->auxVelocGraph->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->auxVelocGraph->graph(0)->removeDataBefore(key-8);
    ui->auxVelocGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxVelocGraph->graph(0)->rescaleValueAxis();
    ui->auxVelocGraph->graph(1)->rescaleValueAxis(true);
}

void MainWindow::addAccelData(double key, double value0, double value1)
{
    ui->auxAccelGraph->graph(0)->addData(key, value0);
    ui->auxAccelGraph->graph(1)->addData(key, value1);
    // set data of dots:
    ui->auxAccelGraph->graph(2)->clearData();
    ui->auxAccelGraph->graph(2)->addData(key, value0);
    ui->auxAccelGraph->graph(3)->clearData();
    ui->auxAccelGraph->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->auxAccelGraph->graph(0)->removeDataBefore(key-8);
    ui->auxAccelGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxAccelGraph->graph(0)->rescaleValueAxis();
    ui->auxAccelGraph->graph(1)->rescaleValueAxis(true);
}

void MainWindow::addUpdtData(double key, double value0, double value1)
{
    ui->auxUpDtGraph->graph(0)->addData(key, value0);
    ui->auxUpDtGraph->graph(1)->addData(key, value1);
    // set data of dots:
    ui->auxUpDtGraph->graph(2)->clearData();
    ui->auxUpDtGraph->graph(2)->addData(key, value0);
    ui->auxUpDtGraph->graph(3)->clearData();
    ui->auxUpDtGraph->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->auxUpDtGraph->graph(0)->removeDataBefore(key-8);
    ui->auxUpDtGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxUpDtGraph->graph(0)->rescaleValueAxis();
    ui->auxUpDtGraph->graph(1)->rescaleValueAxis(true);
}

void MainWindow::addLowdtData(double key, double value0, double value1)
{
    ui->auxLowDtGraph->graph(0)->addData(key, value0);
    ui->auxLowDtGraph->graph(1)->addData(key, value1);
    // set data of dots:
    ui->auxLowDtGraph->graph(2)->clearData();
    ui->auxLowDtGraph->graph(2)->addData(key, value0);
    ui->auxLowDtGraph->graph(3)->clearData();
    ui->auxLowDtGraph->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->auxLowDtGraph->graph(0)->removeDataBefore(key-8);
    ui->auxLowDtGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxLowDtGraph->graph(0)->rescaleValueAxis();
    ui->auxLowDtGraph->graph(1)->rescaleValueAxis(true);
}

void MainWindow::addRotatData(double key, double value0, double value1)
{
    ui->auxRotatGraph->graph(0)->addData(key, value0);
    ui->auxRotatGraph->graph(1)->addData(key, value1);
    // set data of dots:
    ui->auxRotatGraph->graph(2)->clearData();
    ui->auxRotatGraph->graph(2)->addData(key, value0);
    ui->auxRotatGraph->graph(3)->clearData();
    ui->auxRotatGraph->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->auxRotatGraph->graph(0)->removeDataBefore(key-8);
    ui->auxRotatGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxRotatGraph->graph(0)->rescaleValueAxis();
    ui->auxRotatGraph->graph(1)->rescaleValueAxis(true);
}

void MainWindow::realtimeDataSlot()
{

    // calculate two new data points:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;

    double value0 = /*qSin(key);*/ qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
    double value1 = /*qCos(key); */qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
    double x = qCos(key);
    double y = qSin(key);

    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {

      // add data to lines:
      switch (mainGraphDisplay)
      {
          case (VEL):
          addMainData(key, value0, (double)ui->velSpinBox->value());
          ui->label_13->setText(QString::number(maxVel) + " rad/sec");
          ui->label_12->setText(QString::number(value0) + " rad/sec");
          break;

          case (ACC):
          addMainData(key, value1, (double)ui->accSpinBox->value());
          ui->label_13->setText(QString::number(maxAcc) + " rad/sec<sup>2</sup>");
          ui->label_12->setText(QString::number(value1) + " rad/sec<sup>2</sup>");
          break;

          case (UDT):
          addMainData(key, x, y);
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y));
          break;

          case (LDT):
          addMainData(key, x, y);
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y));
          break;

          case (ROT):
          addMainData(key, value0 / 3 * 2, 0);
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y));
          break;
      }

      //add data to aux graphs
      addVelocData(key, value0, (double)ui->velSpinBox->value());
      addAccelData(key, value1, (double)ui->accSpinBox->value());
      addUpdtData(key, x, y);
      addLowdtData(key, x, y);
      addRotatData(key, value0 / 3 * 2, 0);

      lastPointKey = key;

    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->maingraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->maingraph->replot();

    ui->auxVelocGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxVelocGraph->replot();

    ui->auxAccelGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxAccelGraph->replot();

    ui->auxUpDtGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxUpDtGraph->replot();

    ui->auxLowDtGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxLowDtGraph->replot();

    ui->auxRotatGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxRotatGraph->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;

    //for max values
    if (value0 > maxVel)
        maxVel = value0;

    if (value1 > maxAcc)
        maxAcc = value1;

    //show fps and data points in statusbar
    if (key-lastFpsKey > .5 && ui->stackedWidget->currentIndex() == 1) // average fps over .5 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->maingraph->graph(0)->data()->count()+ui->maingraph->graph(1)->data()->count())
            , 0);

      lastFpsKey = key;
      frameCount = 0;
    }

    //don't show if your not on the performance view
    if(ui->stackedWidget->currentIndex() != 1)
    {
        ui->statusBar->clearMessage();
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
    ui->velSpinBox->setValue(value);
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    ui->accSpinBox->setValue(value);
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    ui->doubleSpinBox_3->setValue(value);
}


void MainWindow::on_actionMetric_triggered()
{
    ui->actionEmperial->setChecked(false);
    ui->label_2->setText("rad/sec");
    ui->label_4->setText("rad/sec<sup>2</sup>");
    ui->label_6->setText("rad/sec<sup>3</sup>");
}

void MainWindow::on_actionEmperial_triggered()
{
    ui->actionMetric->setChecked(false);
    ui->label_2->setText("deg/sec");
    ui->label_4->setText("deg/sec<sup>2</sup>");
    ui->label_6->setText("deg/sec<sup>3</sup>");
}

void MainWindow::on_pushButton_clicked()
{
    stopplayer->stop();
    goplayer->stop();
    if (playSounds)
    {
        goplayer->setVolume(100);
        goplayer->play();
    }
    double vel = ui->velSpinBox->value();
    double acc = ui->accSpinBox->value();
    double jerk = ui->doubleSpinBox_3->value();
    ui->textBrowser->append(QString("Flywheel controlled to %1 rad/sec,"
                                    " %2 rad/sec<sup>2</sup>, %3 rad/sec<sup>3</sup>"
                                    " at %4")
                            .arg(vel).arg(acc).arg(jerk)
                            .arg(QTime::currentTime().toString()));
}

void MainWindow::on_actionDarth_Vader_triggered()
{
    playSounds = true;
    ui->actionNone->setChecked(false);
    ui->actionDefault->setChecked(false);
    goplayer->setMedia(QUrl("qrc:/sounds/sounds/I-am-altering-the-deal.wav"));
    stopplayer->setMedia(QUrl("qrc:/sounds/sounds/Darth_Vader_NO!.wav"));
}

void MainWindow::on_pushButton_2_clicked()
{
    stopplayer->stop();
    goplayer->stop();
    if (playSounds)
    {
        stopplayer->setVolume(100);
        stopplayer->play();
    }
    ui->verticalSlider->setValue(0);
    ui->verticalSlider_2->setValue(0);
    ui->verticalSlider_3->setValue(0);
    ui->textBrowser->append(QString("Flywheel Emergency Stop Activated at %1")
                            .arg(QTime::currentTime().toString()));
}

void MainWindow::on_actionNone_triggered()
{
    playSounds = false;
    stopplayer->stop();
    goplayer->stop();
    ui->actionDarth_Vader->setChecked(false);
    ui->actionDefault->setChecked(false);
}

void MainWindow::on_actionDefault_triggered()
{
    playSounds = true;
    ui->actionDarth_Vader->setChecked(false);
    ui->actionNone->setChecked(false);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Space)
        ui->pushButton_2->click();
}

void MainWindow::on_velocButton_clicked()
{
    mainGraphDisplay = VEL;
    ui->label_7->setText("Velocity");
    ui->label_8->setText("Max Velocity");
    clearBorder();
    ui->label_17->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured Value");
    ui->label_11->setText("Expected Value");
}

void MainWindow::on_accelButton_clicked()
{
    mainGraphDisplay = ACC;
    ui->label_7->setText("Acceleration");
    ui->label_8->setText("Max Acceleration");
    clearBorder();
    ui->label_18->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured Value");
    ui->label_11->setText("Expected Value");
}

void MainWindow::on_updtButton_clicked()
{
    mainGraphDisplay = UDT;
    ui->label_7->setText("Upper Displacement");
    ui->label_8->setText("Undefined");
    clearBorder();
    ui->label_19->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("X-value");
    ui->label_11->setText("Y-Value");
}

void MainWindow::on_lowdtButton_clicked()
{
    mainGraphDisplay = LDT;
    ui->label_7->setText("Lower Displacement");
    ui->label_8->setText("Undefined");
    clearBorder();
    ui->label_20->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("X-value");
    ui->label_11->setText("Y-Value");
}

void MainWindow::on_rotatButton_clicked()
{
    mainGraphDisplay = ROT;
    ui->label_7->setText("Rotational Location");
    ui->label_8->setText("Undefined");
    clearBorder();
    ui->label_21->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured Value");
    ui->label_11->setText("Expected Value");
}

void MainWindow::clearBorder()
{
    ui->label_17->setStyleSheet("color: grey; font-size: 11px;");
    ui->label_18->setStyleSheet("color: grey; font-size: 11px;");
    ui->label_19->setStyleSheet("color: grey; font-size: 11px;");
    ui->label_20->setStyleSheet("color: grey; font-size: 11px;");
    ui->label_21->setStyleSheet("color: grey; font-size: 11px;");
    ui->stackedWidget->setCurrentIndex(1);
}
