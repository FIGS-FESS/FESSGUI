#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QTime>
#include <qwidget.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    goplayer = new QMediaPlayer();
    stopplayer = new QMediaPlayer();
    playSounds = false;
    maxVel = 0;

    ui->label_10->setStyleSheet("QLabel {color : blue; }");
    ui->label_11->setStyleSheet("QLabel {color : red; }");

    mainGraph = new RTG(ui->maingraph, true);
    velGraph = new RTG(ui->auxgraph1, false);
    accGraph = new RTG(ui->auxgraph2, false);
    free (mainGraph);
    free (velGraph);
    free (accGraph);


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

    double value0 = /*qSin(key);*/ qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
    double value1 = /*qCos(key); */qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;

    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {

      // add data to lines:
      addMainData(key, value0, value1);
      addAux1Data(key, value0, (double)ui->doubleSpinBox->value());
      addAux2Data(key, value0, (double)ui->doubleSpinBox_2->value());

      lastPointKey = key;
      //output data to csv if recording
      if (isRecording){
          rfs << std::setprecision(4) << std::fixed << key << ", " << value0 << ", " << value1 << "\n";
      }
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

    ui->label_12->setText(QString::number(value0) + " rad/sec");

    if (value0 > maxVel)
    {
        maxVel = value0;
        ui->label_13->setText(QString::number(maxVel) + " rad/sec");
    }

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
    ui->controlButton->setStyleSheet("color:grey;");
    ui->configButton->setStyleSheet("color:black;");
}

void MainWindow::on_configButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->controlButton->setStyleSheet("color:black;");
    ui->configButton->setStyleSheet("color:grey;");
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
    double vel = ui->doubleSpinBox->value();
    double acc = ui->doubleSpinBox_2->value();
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

void MainWindow::on_pushButton_Record_clicked()
{
    if(!isRecording){
        isRecording = true;

        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );

        //Set filename using stringstream
        std::stringstream iss;
        iss << "FlywheelOutput_";
        iss << std::setw(4) << std::setfill('0') << (timeinfo->tm_year)+1900; //setw() and setfill('0') ensure leading zeros are there.
        iss << std::setw(2) << std::setfill('0') << (timeinfo->tm_mon)+1;
        iss << std::setw(2) << std::setfill('0') << timeinfo->tm_mday;
        iss << "_";
        iss << std::setw(2) << std::setfill('0') << timeinfo->tm_hour;
        iss << std::setw(2) << std::setfill('0') << timeinfo->tm_min;
        iss << std::setw(2) << std::setfill('0') << timeinfo->tm_sec;
        iss << ".csv";
        std::string filename = iss.str();

        rfs.open(filename.c_str());
        rfs << "Time" << "Column1," << " Column2," << std::endl;

    }
}

void MainWindow::on_pushButton_StopRecording_clicked()
{
    if (isRecording){
        rfs << std::flush;
        rfs.close();
        isRecording = false;
    }
}
