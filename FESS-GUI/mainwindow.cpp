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

    eStopShortcut = new QAction(this);
    addAction(eStopShortcut);
    eStopShortcut->setShortcut(QKeySequence(Qt::Key_Space));
    connect(eStopShortcut, SIGNAL(triggered(bool)), this, SLOT(on_pushButton_2_clicked()));

    goplayer = new QMediaPlayer(); //sound players
    stopplayer = new QMediaPlayer();
    playSounds = false;
    isRecording = false;
    mainGraphDisplay = VEL; //enum for maingraph
    maxVel = 0;
    maxAcc = 0;
    maxUpDt[0] = 0;
    maxUpDt[1] = 0;
    maxLwDt[0] = 0;
    maxLwDt[1] = 0;

    ui->label_10->setStyleSheet("QLabel {color : blue; }"); //legend
    ui->label_11->setStyleSheet("QLabel {color : red; }");

    mainVelGraph = new RTG(ui->mainVelGraph, true);  //initialize graphs
    mainAccGraph = new RTG(ui->mainAccGraph, true);
    mainUdtGraph = new XYG(ui->mainUdtGraph, true);
    mainLdtGraph = new XYG(ui->mainLdtGraph, true);
    mainRotGraph = new XYG(ui->mainRotGraph, true);

    velGraph = new RTG(ui->auxVelocGraph, false);
    accGraph = new RTG(ui->auxAccelGraph, false);
    updtGraph = new XYG(ui->auxUpDtGraph, false);
    lowdtGraph = new XYG(ui->auxLowDtGraph, false);
    rotatGraph = new XYG(ui->auxRotatGraph, false);


    free (mainVelGraph); //free classes
    free (mainAccGraph);
    free (mainUdtGraph);
    free (mainLdtGraph);
    free (mainRotGraph);

    free (velGraph);
    free (accGraph);
    free (updtGraph);
    free (lowdtGraph);
    free (rotatGraph);


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->mainVelGraph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainVelGraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->mainVelGraph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainVelGraph->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->mainAccGraph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainAccGraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->mainAccGraph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->mainAccGraph->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::addVelocData(double key, double value0, double value1)
{
    ui->mainVelGraph->graph(0)->addData(key, value0);
    ui->mainVelGraph->graph(1)->addData(key, value1);
    // set data of dots:
    ui->mainVelGraph->graph(2)->clearData();
    ui->mainVelGraph->graph(2)->addData(key, value0);
    ui->mainVelGraph->graph(3)->clearData();
    ui->mainVelGraph->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->mainVelGraph->graph(0)->removeDataBefore(key-8);
    ui->mainVelGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->mainVelGraph->graph(0)->rescaleValueAxis();
    ui->mainVelGraph->graph(1)->rescaleValueAxis(true);

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
    ui->mainAccGraph->graph(0)->addData(key, value0);
    ui->mainAccGraph->graph(1)->addData(key, value1);
    // set data of dots:
    ui->mainAccGraph->graph(2)->clearData();
    ui->mainAccGraph->graph(2)->addData(key, value0);
    ui->mainAccGraph->graph(3)->clearData();
    ui->mainAccGraph->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    ui->mainAccGraph->graph(0)->removeDataBefore(key-8);
    ui->mainAccGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->mainAccGraph->graph(0)->rescaleValueAxis();
    ui->mainAccGraph->graph(1)->rescaleValueAxis(true);

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

void MainWindow::addUpdtData(double x, double y)
{
    ui->mainUdtGraph->graph(0)->clearData();
    ui->mainUdtGraph->graph(0)->addData(x, y);

    ui->auxUpDtGraph->graph(0)->clearData();
    ui->auxUpDtGraph->graph(0)->addData(x, y);


}

void MainWindow::addLowdtData(double x, double y)
{
    ui->mainLdtGraph->graph(0)->clearData();
    ui->mainLdtGraph->graph(0)->addData(x, y);

    ui->auxLowDtGraph->graph(0)->clearData();
    ui->auxLowDtGraph->graph(0)->addData(x, y);

}

void MainWindow::addRotatData(double x, double y)
{
    ui->mainRotGraph->graph(0)->clearData();
    ui->mainRotGraph->graph(0)->addData(x, y);

    ui->auxRotatGraph->graph(0)->clearData();
    ui->auxRotatGraph->graph(0)->addData(x, y);
}

void MainWindow::realtimeDataSlot()
{

    // calculate two new data points:
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;

    double value0 = /*qSin(key);*/ qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
    double value1 = /*qCos(key); */qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
    double x = 2*qCos(key) - qCos(2*key);
    double y = 2*qSin(key) - qSin(2*key);

    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {

      // add data to lines:
      switch (mainGraphDisplay)
      {
          case (VEL):
          ui->label_13->setText(QString::number(maxVel) + " rad/sec");
          ui->label_12->setText(QString::number(value0) + " rad/sec");
          break;

          case (ACC):
          ui->label_13->setText(QString::number(maxAcc) + " rad/sec<sup>2</sup>");
          ui->label_12->setText(QString::number(value1) + " rad/sec<sup>2</sup>");
          break;

          case (UDT):
          ui->label_13->setText(QString::number(maxUpDt[0]) + ", " + QString::number(maxUpDt[1]));
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y));
          break;

          case (LDT):
          ui->label_13->setText(QString::number(maxLwDt[0]) + ", " + QString::number(maxLwDt[1]));
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y));
          break;

          case (ROT):
          ui->label_13->setText("");
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y));
          break;
      }

      //add data to graphs
      addVelocData(key, value0, (double)ui->velSpinBox->value());
      addAccelData(key, value1, (double)ui->accSpinBox->value());
      addUpdtData(x, y);
      addLowdtData(y, x);
      addRotatData(qCos(key), qSin(key));

	  //output data to csv if recording
      if (isRecording){
          rfs << std::setprecision(4) << std::fixed << key << ", " << value0 << ", " << value1 << ", " << x << ", " << y << ", " << "\n";
      }
	  
      lastPointKey = key;

    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->mainVelGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->mainVelGraph->replot();

    ui->auxVelocGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxVelocGraph->replot();

    ui->mainAccGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->mainAccGraph->replot();

    ui->auxAccelGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxAccelGraph->replot();

    ui->mainUdtGraph->replot();
    ui->auxUpDtGraph->replot();

    ui->mainLdtGraph->replot();
    ui->auxLowDtGraph->replot();

    ui->mainRotGraph->replot();
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

    if (qFabs(x) > qFabs(maxUpDt[0]))
        maxUpDt[0] = x;

    if (qFabs(y) > qFabs(maxUpDt[1]))
        maxUpDt[1] = y;

    if (qFabs(x) > qFabs(maxLwDt[0]))
        maxLwDt[0] = x;

    if (qFabs(y) > qFabs(maxLwDt[1]))
        maxLwDt[1] = y;

    //show fps and data points in statusbar
    if (key-lastFpsKey > .5 && ui->stackedWidget->currentIndex() == 1) // average fps over .5 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->mainVelGraph->graph(0)->data()->count()+ui->mainVelGraph->graph(1)->data()->count())
            , 0);

      lastFpsKey = key;
      frameCount = 0;
      if(uptime.isValid())
          ui->label_14->setText(QString::number(uptime.elapsed() / 1000));
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

void MainWindow::on_performButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
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

    uptime.start();
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

    uptime.invalidate();
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
    if(event->key() == Qt::Key_Escape)
    {
       //exit
    }
}


void MainWindow::on_velocButton_clicked()
{
    mainGraphDisplay = VEL;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(0);
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
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(1);
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
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(2);
    ui->label_7->setText("Upper Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->label_19->setStyleSheet("color: black; font-size: 14px;");

    ui->label_11->setText("");
}

void MainWindow::on_lowdtButton_clicked()
{
    mainGraphDisplay = LDT;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(3);
    ui->label_7->setText("Lower Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->label_20->setStyleSheet("color: black; font-size: 14px;");

    ui->label_11->setText("");
}

void MainWindow::on_rotatButton_clicked()
{
    mainGraphDisplay = ROT;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(4);
    ui->label_7->setText("Rotational Location");
    ui->label_8->setText("");
    clearBorder();
    ui->label_21->setStyleSheet("color: black; font-size: 14px;");

    ui->label_11->setText("");
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


void MainWindow::on_actionStart_Recording_triggered()
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
        rfs << "Time, " << "Value0," << " Value 1," << " X," << " Y," << std::endl;

        ui->actionStart_Recording->setEnabled(false);
        ui->actionStop_Recording->setEnabled(true);

        ui->textBrowser->append(QString("Output Recording Started at %1")
                                .arg(QTime::currentTime().toString()));
    
	}
}

void MainWindow::on_actionStop_Recording_triggered()
{
    if (isRecording){
        rfs << std::flush;
        rfs.close();

        isRecording = false;
        ui->actionStart_Recording->setEnabled(true);
        ui->actionStop_Recording->setEnabled(false);

        ui->textBrowser->append(QString("Output Recording Stopped at %1")
                                .arg(QTime::currentTime().toString()));
    }
}

void MainWindow::on_eStopKey_keySequenceChanged(const QKeySequence &keySequence)
{
    eStopShortcut->setShortcut(keySequence);
}

void MainWindow::on_maxVel_textChanged(const QString &arg1)
{
    ui->velSpinBox->setMaximum(arg1.toInt());
    ui->verticalSlider->setMaximum(arg1.toInt());
}

void MainWindow::on_maxAccel_textChanged(const QString &arg1)
{
    ui->accSpinBox->setMaximum(arg1.toInt());
    ui->verticalSlider_2->setMaximum(arg1.toInt());
}
