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

    flywheelOperation = new FlywheelOperation(); //contains methods for getting and setting flywheel variables

    expectedVelocity = ui->velocitySpinBox->value();    //initialize expected values based on spinbox values
    expectedAcceleration = ui->accelerationSpinBox->value();
    expectedJerk = ui->jerkSpinBox->value();

    eStopShortcut = new QAction(this);  //setting up the emergency stop shortcut
    addAction(eStopShortcut);
    eStopShortcut->setShortcut(QKeySequence(Qt::Key_Space));
    connect(eStopShortcut, SIGNAL(triggered(bool)), this, SLOT(on_emergencyStopButton_clicked()));

    ui->eStopKey->setKeySequence(eStopShortcut->shortcut()); //E stop shortcut can be user defined

    goplayer = new QMediaPlayer(); //sound players
    stopplayer = new QMediaPlayer();

    recording = new RecordingOperation();  //recording values to file

    ui->pushButton_ApplySettings->setEnabled(false);  //gray out apply settings button by default

    QSettings settings("settings.ini", QSettings::IniFormat);  //settings file

    if(settings.contains("maxVel")){                                            //Set max values in slider and spinbox
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

    /*******************************************************
    The following code initializes all the graphs. There are
    5 graphs, with a main window and auxillary window each.
    Parameters like labels and fill colors
    are also initialized here.
    *******************************************************/

    QColor measuredColor = QColor(Qt::blue), expectedColor = QColor(Qt::red);
    QColor xColor = QColor(Qt::green), yColor = QColor(Qt::magenta);
    QColor upperColor = QColor(255, 165, 0), lowerColor = QColor(Qt::cyan), rotationalColor = QColor(Qt::black);
    QColor fillColor = QColor(240, 255, 200);

    velocityGraph = new ScrollingTimeGraph(this, ui->mainVelGraph, ui->auxVelocGraph, measuredColor, expectedColor, "RPM");
    velocityGraph->setFill(fillColor);
    accelerationGraph = new ScrollingTimeGraph(this, ui->mainAccGraph, ui->auxAccelGraph, measuredColor, expectedColor, "rad/s^2");
    accelerationGraph->setFill(fillColor);
    lowerDisplacementGraph =  new ScrollingTimeGraph(this, ui->mainLdtGraph, ui->auxLowDtGraph, xColor, yColor, "mm");
    upperDisplacementGraph = new ScrollingTimeGraph(this, ui->mainUdtGraph, ui->auxUpDtGraph, xColor, yColor, "mm");

    displacementGraph = new LocationGraph(ui->mainXYGraph, ui->auxXYGraph, upperColor, lowerColor);
    rotationGraph = new LocationGraph(ui->mainRotGraph, ui->auxRotatGraph, rotationalColor);

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    dataTimer = new QTimer(this);
    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realtimeDataSlot()  //Important function. This is repeatedly called
{                                    //as quickly as it can by the timer (line 107)
    // calculate two new data points:
    double currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0; //currentTime is the current time
    static double lastPointTime = 0;

    double actualVelocity = flywheelOperation->getVelocity();               //get all the actual values
    double actualAcceleration = flywheelOperation->getAcceleration();
    QPointF upperDisplacement = flywheelOperation->getUpperDisplacement();
    QPointF lowerDisplacement = flywheelOperation->getLowerDisplacement();
    QPointF rotationalPosition = flywheelOperation->getRotationalPosition();

    if (currentTime-lastPointTime > 0.01) // at most add point every 10 ms
    {

        //this switch is necessary because the text changes depending on what graph you have in the main display
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
        velocityGraph->addData(currentTime, actualVelocity, expectedVelocity);
        accelerationGraph->addData(currentTime, actualAcceleration, expectedAcceleration);
        upperDisplacementGraph->addData(currentTime, upperDisplacement.x(), upperDisplacement.y());
        lowerDisplacementGraph->addData(currentTime, lowerDisplacement.x(), lowerDisplacement.y());

        displacementGraph->addData(upperDisplacement.x(), upperDisplacement.x(), lowerDisplacement.x(), lowerDisplacement.y());
        rotationGraph->addData(rotationalPosition.x(), rotationalPosition.y());

        //output data to csv if recording
        if (isRecording){
            recording->Record(currentTime, actualVelocity, actualAcceleration,
                              upperDisplacement.x(), upperDisplacement.y(),
                              lowerDisplacement.x(), lowerDisplacement.y(),
                              rotationalPosition.x(), rotationalPosition.y());
        }

        lastPointTime = currentTime;
    }

    // calculate frames per second:
    static double lastFpsTime;
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
    if (currentTime-lastFpsTime > .5 && ui->stackedWidget->currentIndex() == 1) // average fps over .5 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
                .arg(frameCount/(currentTime-lastFpsTime), 0, 'f', 0)
                .arg(ui->mainVelGraph->graph(0)->data()->count()+ui->mainVelGraph->graph(1)->data()->count())
            , 0);

      lastFpsTime = currentTime;
      frameCount = 0;
      if(uptime.isValid())
          ui->label_14->setText(QString::number(uptime.elapsed() / 1000)); //uptime is given in milliseconds
    }

    //don't show if your not on the performance view
    if(ui->stackedWidget->currentIndex() != 1)
    {
        ui->statusBar->clearMessage();
    }
}

MainWindow::~MainWindow()  //destructor
{
    delete ui;
}

void MainWindow::on_controlButton_clicked()  //change to control page
{
    ui->stackedWidget->setCurrentIndex(0);  //this is index zero on the stackedwidget
}

void MainWindow::on_performButton_clicked()  //change to performance monitor page
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_configButton_clicked()  //change to configuration page
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_velocitySlider_valueChanged(int velocity)  //reflect sliders value on spinboxes
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

void MainWindow::on_velocitySpinBox_valueChanged(double velocity)  //reflect spinboxes value on sliders
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

void MainWindow::on_goButton_clicked()  //when you hit the go button
{
    expectedVelocity = ui->velocitySpinBox->value();  //get the expected values
    expectedAcceleration = ui->accelerationSpinBox->value();
    expectedJerk = ui->jerkSpinBox->value();

    stopplayer->stop();  //stop sounds so they dont overlap
    goplayer->stop();

    uptime.start();  //start the uptime
    if (playSounds)  //play the sound
    {
        goplayer->setVolume(100);
        goplayer->play();
    }
    //Pass information on to text browser to be displayed
    ui->textBrowser->append(QString("Flywheel controlled to %1 RPM,"
                                    " %2 rad/sec<sup>2</sup>, %3 rad/sec<sup>3</sup>"
                                    " at %4")
                            .arg(expectedVelocity).arg(expectedAcceleration).arg(expectedJerk)
                            .arg(QTime::currentTime().toString()));
}

void MainWindow::on_actionDarth_Vader_triggered() //darth vader option
{
    playSounds = true;
    ui->actionNone->setChecked(false);
    ui->actionDefault->setChecked(false);
    goplayer->setMedia(QUrl("qrc:/sounds/sounds/I-am-altering-the-deal.wav"));
    stopplayer->setMedia(QUrl("qrc:/sounds/sounds/Darth_Vader_NO!.wav"));
}

void MainWindow::on_emergencyStopButton_clicked()  //when you hit emergency stop button
{
    stopplayer->stop(); //stop sounds
    goplayer->stop();

    uptime.invalidate();  //stop uptime
    if (playSounds)
    {
        stopplayer->setVolume(100);
        stopplayer->play();
    }
    ui->velocitySlider->setValue(0);      //set all values to zero
    ui->accelerationSlider->setValue(0);
    ui->jerkSlider->setValue(0);
    //Pass information on to text browswer
    ui->textBrowser->append(QString("Flywheel Emergency Stop Activated at %1")
                            .arg(QTime::currentTime().toString()));
}

void MainWindow::on_actionNone_triggered() //no sounds
{
    playSounds = false;
    stopplayer->stop();
    goplayer->stop();
    ui->actionDarth_Vader->setChecked(false);
    ui->actionDefault->setChecked(false);
}

void MainWindow::on_actionDefault_triggered() //default sounds
{
    playSounds = true;
    ui->actionDarth_Vader->setChecked(false);
    ui->actionNone->setChecked(false);
}

void MainWindow::on_velocButton_clicked()  //These "buttons" are the auxillary graphs
{
    mainGraphDisplay = VEL;             //enum for which display you're on
    ui->stackedWidget->setCurrentIndex(2); //if you hit an auxillary graph it brings the performance page into focus
    ui->stackedWidget_2->setCurrentIndex(0); //this stacked widget has all the main graphs. index zero is the velocity graph
    ui->label_7->setText("Velocity");
    ui->label_8->setText("Max Velocity");
    clearBorder();  //change text labels to default
    ui->velLabel->setStyleSheet("color: black; font-size: 14px;"); //make the label larger to emphasize focus

    ui->label_10->setText("Measured Value");
    ui->label_10->setStyleSheet("QLabel {color :" + velocityGraph->primaryColor.name() + "; }");
    ui->label_11->setText("Expected Value");
    ui->label_11->setStyleSheet("QLabel {color :" + velocityGraph->secondaryColor.name() + "; }");
}

void MainWindow::on_accelButton_clicked()
{
    mainGraphDisplay = ACC;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(1); //index one is the acceleration graph
    ui->label_7->setText("Acceleration");
    ui->label_8->setText("Max Acceleration");
    clearBorder();
    ui->accLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured Value");
    ui->label_10->setStyleSheet("QLabel {color :" + accelerationGraph->primaryColor.name() + "; }");
    ui->label_11->setText("Expected Value");
    ui->label_11->setStyleSheet("QLabel {color :" + accelerationGraph->secondaryColor.name() + "; }");
}

void MainWindow::on_updtButton_clicked()
{
    mainGraphDisplay = UDT;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(2);   //index two is the upper displacement graph
    ui->label_7->setText("Upper X,Y Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->upDtLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured X");
    ui->label_10->setStyleSheet("QLabel {color :" + upperDisplacementGraph->primaryColor.name() + "; }");
    ui->label_11->setText("Measured Y");
    ui->label_11->setStyleSheet("QLabel {color :" + upperDisplacementGraph->secondaryColor.name() + "; }");
}

void MainWindow::on_lowdtButton_clicked()
{
    mainGraphDisplay = LDT;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(3); //index three is the lower displacement graph
    ui->label_7->setText("Lower X,Y Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->lowDtLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Measured X");
    ui->label_10->setStyleSheet("QLabel {color :" + lowerDisplacementGraph->primaryColor.name() + "; }");
    ui->label_11->setText("Measured Y");
    ui->label_11->setStyleSheet("QLabel {color :" + lowerDisplacementGraph->secondaryColor.name() + "; }");
}

void MainWindow::on_XYButton_clicked()
{
    mainGraphDisplay = XYD;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(4);  //index four is the xy graph
    ui->label_7->setText("X,Y Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->xyLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Upper Displacement");
    ui->label_10->setStyleSheet("QLabel {color :" + displacementGraph->primaryColor.name() + "; }");
    ui->label_11->setText("Lower Displacement");
    ui->label_11->setStyleSheet("QLabel {color :" + displacementGraph->secondaryColor.name() + "; }");
}

void MainWindow::on_rotatButton_clicked()
{
    mainGraphDisplay = ROT;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(5);  //index five is the rotational location graph
    ui->label_7->setText("Rotational Location");
    ui->label_8->setText("");
    clearBorder();
    ui->rotLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Rotational Location");
    ui->label_10->setStyleSheet("QLabel {color :" + rotationGraph->primaryColor.name() + "; }");
    ui->label_11->setText("");
}

//todo: change the name of this function to something that actually describes it
void MainWindow::clearBorder()  //resets the text styles back to default
{                               //notice this is called before changing the font in the above functions
    ui->velLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->accLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->upDtLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->lowDtLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->xyLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->rotLabel->setStyleSheet("color: grey; font-size: 11px;");
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_actionStart_Recording_triggered()  //when you hit 'start recording' in the options
{
    if(!isRecording){
        isRecording = true;
        recording->Start();

        ui->actionStart_Recording->setEnabled(false);
        ui->actionStop_Recording->setEnabled(true);
        //put information into text browser
        ui->textBrowser->append(QString("Output Recording Started at %1")
                                .arg(QTime::currentTime().toString()));
    
	}
}

void MainWindow::on_actionStop_Recording_triggered()  //when you hit 'stop recording' in the options
{
    if (isRecording){

        //recording->Stop(); <-should this be here?
        isRecording = false;
        ui->actionStart_Recording->setEnabled(true);
        ui->actionStop_Recording->setEnabled(false);
        //put information in the text browswer
        ui->textBrowser->append(QString("Output Recording Stopped at %1")
                                .arg(QTime::currentTime().toString()));
    }
}


void MainWindow::on_pushButton_ApplySettings_clicked() //when you hit the apply settings button
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    //qDebug(settings.fileName().toLocal8Bit());


    QString password = ui->lineEditPassword->text();

    QString result = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Sha512));

    //ui->textBrowser->append(QString(result));


    if(passwordMatches(password)){  //if the password is correct
        QString newMaxVel = ui->maxVel->text();   //update values
        QString newMaxAcc = ui->maxAccel->text();
        QKeySequence newStopKey = ui->eStopKey->keySequence();

        if(!newMaxVel.isEmpty()){  //change range on input methods
            ui->velocitySpinBox->setMaximum(newMaxVel.toInt());
            ui->velocitySlider->setMaximum(newMaxVel.toInt());
            ui->velocitySlider->setTickInterval(newMaxVel.toInt() / 5);
            settings.setValue("maxVel", newMaxVel);  //update settings file
        }
        if(!newMaxAcc.isEmpty()){
            ui->accelerationSpinBox->setMaximum(newMaxAcc.toInt());
            ui->accelerationSlider->setMaximum(newMaxAcc.toInt());
            ui->accelerationSlider->setTickInterval(newMaxAcc.toInt() / 5);
            settings.setValue("maxAcc", newMaxAcc);
        }
        if(!newStopKey.isEmpty()){  //set the new shortcut
            eStopShortcut->setShortcut(newStopKey);
            settings.setValue("stopKey", newStopKey.toString());
        }
        ui->textBrowser->append("Configuration changed");
        ui->lineEditPassword->clear();  //clear the password field
        ui->pushButton_ApplySettings->setEnabled(false); //gray the apply button back out
    } else {
        ui->textBrowser->append("Wrong password");  //or if you got the password wrong
        ui->maxVel->setText(QString::number(ui->velocitySlider->maximum()));  //change the text back to what it was
        ui->maxAccel->setText(QString::number(ui->accelerationSlider->maximum()));
        ui->eStopKey->setKeySequence(eStopShortcut->shortcut());
    }
}

void MainWindow::on_actionSet_Reset_Password_triggered(){  //show the password dialog box
    SetPasswordDialog* d = new SetPasswordDialog();

    d->show();


}

void MainWindow::on_lineEditPassword_textEdited(const QString &password)
//this function enables the apply button when you type characters into the password field
{
    if (password.isEmpty())
        ui->pushButton_ApplySettings->setEnabled(false);
    else
        ui->pushButton_ApplySettings->setEnabled(true);
}


