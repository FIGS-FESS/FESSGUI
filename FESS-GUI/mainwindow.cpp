#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setpassworddialog.h"
#include "flywheeloperation.h"
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

    flywheelOperation = new FlywheelOperation();

    expectedVelocity = ui->velocitySpinBox->value();
    expectedAcceleration = ui->accelerationSpinBox->value();
    expectedJerk = ui->jerkSpinBox->value();

    eStopShortcut = new QAction(this);
    addAction(eStopShortcut);
    eStopShortcut->setShortcut(QKeySequence(Qt::Key_Space));
    connect(eStopShortcut, SIGNAL(triggered(bool)), this, SLOT(on_emergencyStopButton_clicked()));

    goplayer = new QMediaPlayer(); //sound players
    stopplayer = new QMediaPlayer();

    recording = new RecordingOperation();

    ui->pushButton_ApplySettings->setEnabled(false);

    QSettings settings("settings.ini", QSettings::IniFormat);

    ui->eStopKey->setKeySequence(eStopShortcut->shortcut());

    if(settings.contains("maxVel")){
        ui->velocitySpinBox->setMaximum(settings.value("maxVel", "").toInt());
        ui->velocitySlider->setMaximum(settings.value("maxVel", "").toInt());
        ui->maxVel->setText((settings.value("maxVel", "").toString()));
    }
    if(settings.contains("maxAcc")){
        ui->accelerationSpinBox->setMaximum(settings.value("maxAcc", "").toInt());
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

    graphOperation = new GraphOperation();
    graphOperation->SetupRTG(ui->mainVelGraph, true);  //initialize graphs
    ui->mainVelGraph->yAxis->setLabel("RPM");
    ui->mainVelGraph->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    graphOperation->SetupRTG(ui->mainAccGraph, true);
    ui->mainAccGraph->yAxis->setLabel("rad/s^2");
    ui->mainAccGraph->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    graphOperation->SetupRTG(ui->mainUdtGraph, true);
    ui->mainUdtGraph->yAxis->setLabel("mm");

    graphOperation->SetupRTG(ui->mainLdtGraph, true);
    ui->mainLdtGraph->yAxis->setLabel("mm");

    graphOperation->SetupXYG(ui->mainXYGraph, true);
    graphOperation->SetupXYG(ui->mainRotGraph, true);

    graphOperation->SetupRTG(ui->auxVelocGraph, false);
    ui->auxVelocGraph->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    graphOperation->SetupRTG(ui->auxAccelGraph, false);
    ui->auxAccelGraph->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    graphOperation->SetupRTG(ui->auxUpDtGraph, false);
    graphOperation->SetupRTG(ui->auxLowDtGraph, false);
    graphOperation->SetupXYG(ui->auxXYGraph, false);
    graphOperation->SetupXYG(ui->auxRotatGraph, false);

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

    double actualVelocity = flywheelOperation->getVelocity();
    double actualAcceleration = flywheelOperation->getAcceleration();
    QPointF upperDisplacement = flywheelOperation->getUpperDisplacement();
    QPointF lowerDisplacement = flywheelOperation->getLowerDisplacement();
    QPointF rotationalPosition = flywheelOperation->getRotationalPosition();

    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {

      // add data to lines:
      switch (mainGraphDisplay)
      {
          case (VEL):
          ui->label_13->setText(QString::number(maxVel) + " RPM");
          ui->label_12->setText(QString::number(actualVelocity) + " RPM");
          break;

          case (ACC):
          ui->label_13->setText(QString::number(maxAcc) + " rad/s<sup>2</sup>");
          ui->label_12->setText(QString::number(actualAcceleration) + " rad/s<sup>2</sup>");
          break;

          case (UDT):
          ui->label_13->setText(QString::number(maxUpDt[0]) + ", " + QString::number(maxUpDt[1]) + " mm");
          ui->label_12->setText(QString::number(upperDisplacement.x()) + ", " + QString::number(upperDisplacement.y()) + " mm");
          break;

          case (LDT):
          ui->label_13->setText(QString::number(maxLwDt[0]) + ", " + QString::number(maxLwDt[1]) + " mm");
          ui->label_12->setText(QString::number(lowerDisplacement.x()) + ", " + QString::number(lowerDisplacement.y()) + " mm");
          break;

          case (XYD):
          //todo: correct this
          ui->label_13->setText(QString::number(maxUpDt[0]) + ", " + QString::number(maxUpDt[1]) + " mm");
          ui->label_12->setText(QString::number(upperDisplacement.x()) + ", " + QString::number(lowerDisplacement.y()) + " mm");
          break;

          case (ROT):
          ui->label_13->setText("");
          ui->label_12->setText(QString::number(rotationalPosition.x()) + ", " + QString::number(rotationalPosition.y()));
          break;
      }

      //add data to graphs
      graphOperation->addRTGData(ui->mainVelGraph, key, actualVelocity, expectedVelocity);
      graphOperation->addRTGData(ui->auxVelocGraph, key, actualVelocity, expectedVelocity);
      graphOperation->addRTGData(ui->mainAccGraph, key, actualAcceleration, expectedAcceleration);
      graphOperation->addRTGData(ui->auxAccelGraph, key, actualAcceleration, expectedAcceleration);
      graphOperation->addRTGData(ui->mainUdtGraph, key, upperDisplacement.x(), upperDisplacement.y());
      graphOperation->addRTGData(ui->auxUpDtGraph, key, upperDisplacement.x(), upperDisplacement.y());
      graphOperation->addRTGData(ui->mainLdtGraph, key, lowerDisplacement.x(), lowerDisplacement.y());
      graphOperation->addRTGData(ui->auxLowDtGraph, key, lowerDisplacement.x(), lowerDisplacement.y());

      addXYData(upperDisplacement.x(), upperDisplacement.x(), lowerDisplacement.x(), lowerDisplacement.y());
      addRotatData(rotationalPosition.x(), rotationalPosition.y());

	  //output data to csv if recording
      if (isRecording){
          recording->Record(key, actualVelocity, actualAcceleration,
                            upperDisplacement.x(), upperDisplacement.y(),
                            lowerDisplacement.x(), lowerDisplacement.y(),
                            rotationalPosition.x(), rotationalPosition.y());
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
    if (actualVelocity > maxVel)
        maxVel = actualVelocity;

    if (actualAcceleration > maxAcc)
        maxAcc = actualAcceleration;

    if (qFabs(upperDisplacement.x()) > qFabs(maxUpDt[0]))
        maxUpDt[0] = upperDisplacement.x();

    if (qFabs(upperDisplacement.y()) > qFabs(maxUpDt[1]))
        maxUpDt[1] = upperDisplacement.y();

    if (qFabs(lowerDisplacement.x()) > qFabs(maxLwDt[0]))
        maxLwDt[0] = lowerDisplacement.x();

    if (qFabs(lowerDisplacement.y()) > qFabs(maxLwDt[1]))
        maxLwDt[1] = lowerDisplacement.y();

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

void MainWindow::on_velocitySlider_valueChanged(int velocity)
{
    ui->velocitySpinBox->setValue(velocity);
}

void MainWindow::on_accelerationSlider_valueChanged(int acceleration)
{
    ui->accelerationSpinBox->setValue(acceleration);
}

void MainWindow::on_jerkSlider_valueChanged(int jerk)
{
    ui->jerkSpinBox->setValue(jerk);
}

void MainWindow::on_velocitySpinBox_valueChanged(double velocity)
{
    ui->velocitySlider->setValue((int)velocity);
}

void MainWindow::on_accelerationSpinBox_valueChanged(double acceleration)
{
    ui->accelerationSlider->setValue((int)acceleration);
}

void MainWindow::on_jerkSpinBox_valueChanged(double jerk)
{
    ui->jerkSlider->setValue((int)jerk);
}

void MainWindow::on_goButton_clicked()
{
    expectedVelocity = ui->velocitySpinBox->value();
    expectedAcceleration = ui->accelerationSpinBox->value();
    expectedJerk = ui->jerkSpinBox->value();

    stopplayer->stop();
    goplayer->stop();

    uptime.start();
    if (playSounds)
    {
        goplayer->setVolume(100);
        goplayer->play();
    }
    ui->textBrowser->append(QString("Flywheel controlled to %1 RPM,"
                                    " %2 rad/sec<sup>2</sup>, %3 rad/sec<sup>3</sup>"
                                    " at %4")
                            .arg(expectedVelocity).arg(expectedAcceleration).arg(expectedJerk)
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
        recording->Start();

        ui->actionStart_Recording->setEnabled(false);
        ui->actionStop_Recording->setEnabled(true);

        ui->textBrowser->append(QString("Output Recording Started at %1")
                                .arg(QTime::currentTime().toString()));
    
	}
}

void MainWindow::on_actionStop_Recording_triggered()
{
    if (isRecording){


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
            ui->velocitySpinBox->setMaximum(newMaxVel.toInt());
            ui->velocitySlider->setMaximum(newMaxVel.toInt());
            ui->velocitySlider->setTickInterval(newMaxVel.toInt() / 5);
            settings.setValue("maxVel", newMaxVel);
        }
        if(!newMaxAcc.isEmpty()){
            ui->accelerationSpinBox->setMaximum(newMaxAcc.toInt());
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
        ui->pushButton_ApplySettings->setEnabled(false);
    } else {
        ui->textBrowser->append("Wrong password");
        ui->maxVel->setText(QString::number(ui->velocitySlider->maximum()));
        ui->maxAccel->setText(QString::number(ui->accelerationSlider->maximum()));
        ui->eStopKey->setKeySequence(eStopShortcut->shortcut());
    }
}

void MainWindow::on_actionSet_Reset_Password_triggered(){
    SetPasswordDialog* d = new SetPasswordDialog();

    d->show();


}

void MainWindow::on_lineEditPassword_textEdited(const QString &password)
{
    if (password.isEmpty())
        ui->pushButton_ApplySettings->setEnabled(false);
    else
        ui->pushButton_ApplySettings->setEnabled(true);
}


