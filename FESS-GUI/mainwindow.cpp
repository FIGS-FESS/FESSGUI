#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setpassworddialog.h"
#include <QCryptographicHash>
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

    qsrand(time(NULL));

    eStopShortcut = new QAction(this);
    addAction(eStopShortcut);
    eStopShortcut->setShortcut(QKeySequence(Qt::Key_Space));
    connect(eStopShortcut, SIGNAL(triggered(bool)), this, SLOT(on_emergencyStopButton_clicked()));

    goplayer = new QMediaPlayer(); //sound players
    stopplayer = new QMediaPlayer();

    QSettings settings("settings.ini", QSettings::IniFormat);

    ui->eStopKey->setKeySequence(eStopShortcut->shortcut());

    if(settings.contains("maxVel")){
        ui->velSpinBox->setMaximum(settings.value("maxVel", "").toInt());
        ui->velocitySlider->setMaximum(settings.value("maxVel", "").toInt());
        ui->maxVel->setText((settings.value("maxVel", "").toString()));
    }
    if(settings.contains("maxAcc")){
        ui->accSpinBox->setMaximum(settings.value("maxAcc", "").toInt());
        ui->accelerationSlider->setMaximum(settings.value("maxAcc", "").toInt());
        ui->maxAccel->setText((settings.value("maxAcc", "")).toString());
    }
    if(settings.contains("stopKey")){
        eStopShortcut->setShortcut(QKeySequence::fromString(settings.value("stopKey").toString()));
        ui->eStopKey->setKeySequence(eStopShortcut->shortcut());
    }

    connect(ui->maxVel, SIGNAL(returnPressed()), ui->pushButton_ApplySettings, SIGNAL(clicked()));
    connect(ui->maxAccel, SIGNAL(returnPressed()), ui->pushButton_ApplySettings, SIGNAL(clicked()));
    connect(ui->lineEditPassword, SIGNAL(returnPressed()), ui->pushButton_ApplySettings, SIGNAL(clicked()));

    rtg = new RTG();
    rtg->SetupRTG(ui->mainVelGraph, true);  //initialize graphs
    ui->mainVelGraph->yAxis->setLabel("RPM");
    ui->mainVelGraph->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    rtg->SetupRTG(ui->mainAccGraph, true);
    ui->mainAccGraph->yAxis->setLabel("rad/s^2");
    ui->mainAccGraph->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    rtg->SetupRTG(ui->mainUdtGraph, true);
    ui->mainUdtGraph->yAxis->setLabel("mm");

    rtg->SetupRTG(ui->mainLdtGraph, true);
    ui->mainLdtGraph->yAxis->setLabel("mm");

    mainXYGraph = new XYG(ui->mainXYGraph, true);
    mainRotGraph = new XYG(ui->mainRotGraph, true);

    rtg->SetupRTG(ui->auxVelocGraph, false);
    ui->auxVelocGraph->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    rtg->SetupRTG(ui->auxAccelGraph, false);
    ui->auxAccelGraph->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    rtg->SetupRTG(ui->auxUpDtGraph, false);
    rtg->SetupRTG(ui->auxLowDtGraph, false);
    xyGraph = new XYG(ui->auxXYGraph, false);
    rotatGraph = new XYG(ui->auxRotatGraph, false);

    free (mainXYGraph);
    free (mainRotGraph);
    free (xyGraph);
    free (rotatGraph);

    // make left and bottom axes transfer their ranges to right and top axes:
    transferAxes(ui->mainVelGraph);
    transferAxes(ui->mainAccGraph);
    transferAxes(ui->mainUdtGraph);
    transferAxes(ui->mainLdtGraph);

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::transferAxes(QCustomPlot* graph){
    connect(graph->xAxis, SIGNAL(rangeChanged(QCPRange)), graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(graph->yAxis, SIGNAL(rangeChanged(QCPRange)), graph->yAxis2, SLOT(setRange(QCPRange)));
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

void MainWindow::addUpdtData(double key, double x, double y)
{
    ui->mainUdtGraph->graph(0)->addData(key, x);
    ui->mainUdtGraph->graph(1)->addData(key, y);
    // set data of dots:
    ui->mainUdtGraph->graph(2)->clearData();
    ui->mainUdtGraph->graph(2)->addData(key, x);
    ui->mainUdtGraph->graph(3)->clearData();
    ui->mainUdtGraph->graph(3)->addData(key, y);
    // remove data of lines that's outside visible range:
    ui->mainUdtGraph->graph(0)->removeDataBefore(key-8);
    ui->mainUdtGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->mainUdtGraph->graph(0)->rescaleValueAxis();
    ui->mainUdtGraph->graph(1)->rescaleValueAxis(true);

    ui->auxUpDtGraph->graph(0)->addData(key, x);
    ui->auxUpDtGraph->graph(1)->addData(key, y);
    // set data of dots:
    ui->auxUpDtGraph->graph(2)->clearData();
    ui->auxUpDtGraph->graph(2)->addData(key, x);
    ui->auxUpDtGraph->graph(3)->clearData();
    ui->auxUpDtGraph->graph(3)->addData(key, y);
    // remove data of lines that's outside visible range:
    ui->auxUpDtGraph->graph(0)->removeDataBefore(key-8);
    ui->auxUpDtGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxUpDtGraph->graph(0)->rescaleValueAxis();
    ui->auxUpDtGraph->graph(1)->rescaleValueAxis(true);
}

void MainWindow::addLowdtData(double key, double x, double y)
{
    ui->mainLdtGraph->graph(0)->addData(key, x);
    ui->mainLdtGraph->graph(1)->addData(key, y);
    // set data of dots:
    ui->mainLdtGraph->graph(2)->clearData();
    ui->mainLdtGraph->graph(2)->addData(key, x);
    ui->mainLdtGraph->graph(3)->clearData();
    ui->mainLdtGraph->graph(3)->addData(key, y);
    // remove data of lines that's outside visible range:
    ui->mainLdtGraph->graph(0)->removeDataBefore(key-8);
    ui->mainLdtGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->mainLdtGraph->graph(0)->rescaleValueAxis();
    ui->mainLdtGraph->graph(1)->rescaleValueAxis(true);

    ui->auxLowDtGraph->graph(0)->addData(key, x);
    ui->auxLowDtGraph->graph(1)->addData(key, y);
    // set data of dots:
    ui->auxLowDtGraph->graph(2)->clearData();
    ui->auxLowDtGraph->graph(2)->addData(key, x);
    ui->auxLowDtGraph->graph(3)->clearData();
    ui->auxLowDtGraph->graph(3)->addData(key, y);
    // remove data of lines that's outside visible range:
    ui->auxLowDtGraph->graph(0)->removeDataBefore(key-8);
    ui->auxLowDtGraph->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    ui->auxLowDtGraph->graph(0)->rescaleValueAxis();
    ui->auxLowDtGraph->graph(1)->rescaleValueAxis(true);
}

void MainWindow::addXYData(double ux, double uy, double lx, double ly)
{
    ui->mainXYGraph->graph(0)->clearData();
    ui->mainXYGraph->graph(0)->addData(ux, uy);

    ui->auxXYGraph->graph(0)->clearData();
    ui->auxXYGraph->graph(0)->addData(ux, uy);

    ui->mainXYGraph->graph(1)->clearData();
    ui->mainXYGraph->graph(1)->addData(lx, ly);

    ui->auxXYGraph->graph(1)->clearData();
    ui->auxXYGraph->graph(1)->addData(lx, ly);
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
          ui->label_13->setText(QString::number(maxVel) + " RPM");
          ui->label_12->setText(QString::number(value0) + " RPM");
          break;

          case (ACC):
          ui->label_13->setText(QString::number(maxAcc) + " rad/s<sup>2</sup>");
          ui->label_12->setText(QString::number(value1) + " rad/s<sup>2</sup>");
          break;

          case (UDT):
          ui->label_13->setText(QString::number(maxUpDt[0]) + ", " + QString::number(maxUpDt[1]) + " mm");
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y) + " mm");
          break;

          case (LDT):
          ui->label_13->setText(QString::number(maxLwDt[0]) + ", " + QString::number(maxLwDt[1]) + " mm");
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y) + " mm");
          break;

          case (XYD):
          ui->label_13->setText(QString::number(maxUpDt[0]) + ", " + QString::number(maxUpDt[1]) + " mm");
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y) + " mm");
          break;

          case (ROT):
          ui->label_13->setText("");
          ui->label_12->setText(QString::number(x) + ", " + QString::number(y));
          break;
      }

      //add data to graphs
      addVelocData(key, value0, (double)ui->velSpinBox->value());
      addAccelData(key, value1, (double)ui->accSpinBox->value());
      addUpdtData(key, x, y);
      addLowdtData(key, y, x);
      addXYData(x, y, y, x);
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

    ui->mainUdtGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->mainUdtGraph->replot();

    ui->auxUpDtGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxUpDtGraph->replot();

    ui->mainLdtGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->mainLdtGraph->replot();

    ui->auxLowDtGraph->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->auxLowDtGraph->replot();

    ui->mainXYGraph->replot();
    ui->auxXYGraph->replot();

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

void MainWindow::on_velocitySlider_valueChanged(int value)
{
    ui->velSpinBox->setValue(value);
}

void MainWindow::on_accelerationSlider_valueChanged(int value)
{
    ui->accSpinBox->setValue(value);
}

void MainWindow::on_jerkSlider_valueChanged(int value)
{
    ui->doubleSpinBox_3->setValue(value);
}

void MainWindow::on_goButton_clicked()
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
    ui->textBrowser->append(QString("Flywheel controlled to %1 RPM,"
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

void MainWindow::on_emergencyStopButton_clicked()
{
    stopplayer->stop();
    goplayer->stop();

    uptime.invalidate();
    if (playSounds)
    {
        stopplayer->setVolume(100);
        stopplayer->play();
    }
    ui->velocitySlider->setValue(0);
    ui->accelerationSlider->setValue(0);
    ui->jerkSlider->setValue(0);
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
    ui->velLabel->setStyleSheet("color: black; font-size: 14px;");

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
    ui->accLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured Value");
    ui->label_11->setText("Expected Value");
}

void MainWindow::on_updtButton_clicked()
{
    mainGraphDisplay = UDT;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(2);
    ui->label_7->setText("Upper X,Y Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->upDtLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured X");
    ui->label_11->setText("Measured Y");
}

void MainWindow::on_lowdtButton_clicked()
{
    mainGraphDisplay = LDT;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(3);
    ui->label_7->setText("Lower X,Y Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->lowDtLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured X");
    ui->label_11->setText("Measured Y");
}

void MainWindow::on_XYButton_clicked()
{
    mainGraphDisplay = XYD;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(4);
    ui->label_7->setText("X,Y Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->xyLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Upper Displacement");
    ui->label_11->setText("Lower Displacement");
}

void MainWindow::on_rotatButton_clicked()
{
    mainGraphDisplay = ROT;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(5);
    ui->label_7->setText("Rotational Location");
    ui->label_8->setText("");
    clearBorder();
    ui->rotLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Rotational Location");
    ui->label_11->setText("");
}

void MainWindow::clearBorder()
{
    ui->velLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->accLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->upDtLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->lowDtLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->xyLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->rotLabel->setStyleSheet("color: grey; font-size: 11px;");
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


void MainWindow::on_pushButton_ApplySettings_clicked()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    //qDebug(settings.fileName().toLocal8Bit());


    QString password = ui->lineEditPassword->text();

    QString result = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Sha512));

    //ui->textBrowser->append(QString(result));


    if(passwordMatches(password)){
        QString newMaxVel = ui->maxVel->text();
        QString newMaxAcc = ui->maxAccel->text();
        QKeySequence newStopKey = ui->eStopKey->keySequence();

        if(!newMaxVel.isEmpty()){
            ui->velSpinBox->setMaximum(newMaxVel.toInt());
            ui->velocitySlider->setMaximum(newMaxVel.toInt());
            ui->velocitySlider->setTickInterval(newMaxVel.toInt() / 5);
            settings.setValue("maxVel", newMaxVel);
        }
        if(!newMaxAcc.isEmpty()){
            ui->accSpinBox->setMaximum(newMaxAcc.toInt());
            ui->accelerationSlider->setMaximum(newMaxAcc.toInt());
            ui->accelerationSlider->setTickInterval(newMaxAcc.toInt() / 5);
            settings.setValue("maxAcc", newMaxAcc);
        }
        if(!newStopKey.isEmpty()){
            settings.setValue("stopKey", newStopKey.toString());
            eStopShortcut->setShortcut(newStopKey);
        }
        ui->textBrowser->append("Configuration changed");
        ui->lineEditPassword->clear();
    } else {
        ui->maxVel->setText(QString::number(ui->velocitySlider->maximum()));
        ui->maxAccel->setText(QString::number(ui->accelerationSlider->maximum()));
        ui->eStopKey->setKeySequence(eStopShortcut->shortcut());
    }
}

void MainWindow::on_actionSet_Reset_Password_triggered(){
    SetPasswordDialog* d = new SetPasswordDialog();

    d->show();

}








