#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windowsnames.h"
#include "errormessages.h"

#include "conversions.h"
#include "setpassworddialog.h"
#include "flywheeloperation.h"
#include "commoninterfacemanager.h"
#include "commoninterfaceselector.h"

#include <ctime>

#include <QTime>
#include <QKeyEvent>

#include <vector>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTimers();
    setUpSignals();
    setUpKeyBindings();

    qsrand(time(NULL));

    this->setWindowTitle(MAINWINDOW_TITLE);

    interfaceManager = new CommonInterfaceManager();
    flywheelOperation = new FlywheelOperation();

    errorHandler = new QErrorMessage(this);
    errorHandler->setWindowTitle(MAINWINDOW_ERROR);

    currentExpectedVelocity = RPMtoRadsPerSecond(ui->velocitySpinBox->value());    //initialize expected values based on spinbox values
    currentExpectedAcceleration = ui->accelerationSpinBox->value();
    currentExpectedJerk = ui->jerkSpinBox->value();

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

    velocityGraph = new ScrollingTimeGraph(this, ui->mainVelGraph, ui->auxVelocGraph, measuredColor, expectedColor, "RPM", 1);
    velocityGraph->setFill(fillColor);
    selectedGraph = velocityGraph;
    accelerationGraph = new ScrollingTimeGraph(this, ui->mainAccGraph, ui->auxAccelGraph, measuredColor, expectedColor, "rad/s²", 1);
    accelerationGraph->setFill(fillColor);
    lowerDisplacementGraph =  new ScrollingTimeGraph(this, ui->mainLdtGraph, ui->auxLowDtGraph, xColor, yColor, "mm", 2);
    upperDisplacementGraph = new ScrollingTimeGraph(this, ui->mainUdtGraph, ui->auxUpDtGraph, xColor, yColor, "mm", 2);

    displacementGraph = new LocationGraph(ui->mainXYGraph, ui->auxXYGraph, std::vector<QColor>{upperColor, lowerColor}, "mm", 2);
    rotationGraph = new LocationGraph(ui->mainRotGraph, ui->auxRotatGraph, std::vector<QColor>{rotationalColor}, "mm", 1);

    // this timer manages the velocity slope. it starts when you hit the go button
    velocitySlopeTimer = new QTimer(this);
    connect(velocitySlopeTimer, SIGNAL(timeout()), this, SLOT(velocitySlope()));

    accelerationSlopeTimer = new QTimer(this);
    connect(accelerationSlopeTimer, SIGNAL(timeout()), this, SLOT(accelerationSlope()));
}

// Signal Setups

void MainWindow::setUpSignals()
{
    connect(ui->actionOpenInterfaceSettings, SIGNAL(triggered(bool)), this, SLOT(openInterfaceSettingsWindow()));
    connect(ui->actionStartInterface, SIGNAL(triggered(bool)), this, SLOT(startFlywheelInterface()));
    connect(ui->actionStopInterface, SIGNAL(triggered(bool)), this, SLOT(stopFlywheelInterface()));
    connect(ui->actionCloseInterface, SIGNAL(triggered(bool)), this, SLOT(closeFlywheelInterface()));

    connect(ui->maxVel, SIGNAL(returnPressed()), ui->pushButton_ApplySettings, SIGNAL(clicked()));
    connect(ui->maxAccel, SIGNAL(returnPressed()), ui->pushButton_ApplySettings, SIGNAL(clicked()));
    connect(ui->lineEditPassword, SIGNAL(returnPressed()), ui->pushButton_ApplySettings, SIGNAL(clicked()));
}

void MainWindow::setUpKeyBindings()
{
    eStopShortcut = new QAction(this);  //setting up the emergency stop shortcut
    addAction(eStopShortcut);
    eStopShortcut->setShortcut(QKeySequence(Qt::Key_Space));

    connect(eStopShortcut, SIGNAL(triggered(bool)), this, SLOT(on_emergencyStopButton_clicked()));

    ui->eStopKey->setKeySequence(eStopShortcut->shortcut()); //E stop shortcut can be user defined
}

void MainWindow::setTimers()
{
    graphRefreshTimer = new QTimer(this);
    flywheelRefreshTimer = new QTimer(this);

    graphRefreshRate = 100;
    flywheelRefreshRate = 200;

    graphRefreshTimer->setInterval(refreshRateToMS(graphRefreshRate));
    flywheelRefreshTimer->setInterval(refreshRateToMS(flywheelRefreshRate));

    graphRefreshTimer->start(refreshRateToMS(graphRefreshRate));

    connect(graphRefreshTimer, SIGNAL(timeout()), SLOT(realtimeDataSlot()));
    connect(flywheelRefreshTimer, SIGNAL(timeout()), SLOT(runFlywheelOperations()));
}

void MainWindow::realtimeDataSlot()  //Important function. This is repeatedly called
{
    //at the refresh rate defined by the timer
    // calculate two new data points:
    double currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0; //currentTime is the current time

    double actualVelocity = flywheelOperation->getVelocity();               //get all the actual values
    double actualAcceleration = flywheelOperation->getAcceleration();
    QPointF upperDisplacement = flywheelOperation->getUpperDisplacement();
    QPointF lowerDisplacement = flywheelOperation->getLowerDisplacement();
    QPointF rotationalPosition = flywheelOperation->getRotationalPosition();

    ui->label_13->setText(selectedGraph->maxDisplay());
    ui->label_12->setText(selectedGraph->currentDisplay());

    //add data to graphs
    velocityGraph->addData(currentTime, actualVelocity, radsPerSecondToRPM(currentExpectedVelocity));
    accelerationGraph->addData(currentTime, actualAcceleration, currentExpectedAcceleration);
    upperDisplacementGraph->addData(currentTime, upperDisplacement.x(), upperDisplacement.y());
    lowerDisplacementGraph->addData(currentTime, lowerDisplacement.x(), lowerDisplacement.y());

    displacementGraph->addData(std::vector<QPointF> {upperDisplacement, lowerDisplacement});
    rotationGraph->addData(std::vector<QPointF> {rotationalPosition});

    //output data to csv if recording
    if (isRecording){
        recording->Record(currentTime, actualVelocity, actualAcceleration,
                          upperDisplacement.x(), upperDisplacement.y(),
                          lowerDisplacement.x(), lowerDisplacement.y(),
                          rotationalPosition.x(), rotationalPosition.y());
    }

    // calculate frames per second:
    static double lastFpsTime;
    static int frameCount;
    ++frameCount;

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
    delete errorHandler;
    delete graphRefreshTimer;
    delete flywheelRefreshTimer;
    delete flywheelOperation;
    delete interfaceManager;
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
    velocitySlopeTimer->stop();
    accelerationSlopeTimer->stop();

    targetVelocity = RPMtoRadsPerSecond(ui->velocitySpinBox->value());  //get the expected/target values, get velocity in rad/s
    targetAcceleration = ui->accelerationSpinBox->value();
    currentExpectedJerk = ui->jerkSpinBox->value();

    velocitySlopeTimer->start(10); //run every 10ms
    accelerationSlopeTimer->start(10);


    stopplayer->stop();  //stop sounds so they dont overlap
    goplayer->stop();

    uptime.start();  //start the uptime
    if (playSounds)  //play the sound
    {
        goplayer->setVolume(100);
        goplayer->play();
    }
    //Pass information on to text browser to be displayed
    ui->outputLog->append(QString("Flywheel controlled to %1 RPM,"
                                    " %2 rad/sec<sup>2</sup>, %3 rad/sec<sup>3</sup>"
                                    " at %4")
                            .arg(targetVelocity).arg(targetAcceleration).arg(currentExpectedJerk)
                            .arg(QTime::currentTime().toString()));
}

/*this function manages the slope. It is called every 10ms when you click the go button,
  and stops when you get to your target velocity */
void MainWindow::velocitySlope()
{
    double intervalIncrement = 1000 / velocitySlopeTimer->interval(); //get the correct increment

    if(currentExpectedVelocity <= targetVelocity){ //if the target velocity is greater than the current
        currentExpectedVelocity += currentExpectedAcceleration / intervalIncrement; //increment the velocity
        if(currentExpectedVelocity >= targetVelocity){
            velocitySlopeTimer->stop();
            accelerationSlopeTimer->stop();
            currentExpectedVelocity = targetVelocity; //in case the numbers don't round nicely
            currentExpectedAcceleration = 0;
        }
    }
    else {
        currentExpectedVelocity -= currentExpectedAcceleration / intervalIncrement;
        if(currentExpectedVelocity<=targetVelocity){
            velocitySlopeTimer->stop();
            accelerationSlopeTimer->stop();
            currentExpectedVelocity = targetVelocity;
            currentExpectedAcceleration = 0;
        }
    }
}

void MainWindow::accelerationSlope()
{
    double intervalIncrement = 1000 / accelerationSlopeTimer->interval();

    if(currentExpectedAcceleration <= targetAcceleration){
        currentExpectedAcceleration += currentExpectedJerk / intervalIncrement;
        if(currentExpectedAcceleration >= targetAcceleration){
            accelerationSlopeTimer->stop();
            currentExpectedAcceleration = targetAcceleration;
        }
    }
    else {
        currentExpectedAcceleration -= currentExpectedJerk / intervalIncrement;
        if(currentExpectedAcceleration<=targetAcceleration){
            accelerationSlopeTimer->stop();
            currentExpectedAcceleration = targetAcceleration;
        }
    }
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
    velocitySlopeTimer->stop(); //if your in the middle of changing values
    accelerationSlopeTimer->stop();

    uptime.invalidate();  //stop uptime
    if (playSounds)
    {
        stopplayer->setVolume(100);
        stopplayer->play();
    }
    ui->velocitySlider->setValue(0);      //set all values to zero
    currentExpectedVelocity = 0;
    ui->accelerationSlider->setValue(0);
    currentExpectedAcceleration = 0;
    ui->jerkSlider->setValue(0);
    currentExpectedJerk = 0;
    //Pass information on to text browswer
    ui->outputLog->append(QString("Flywheel Emergency Stop Activated at %1")
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
    selectedGraph = velocityGraph;             //pointer for which display you're on
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
    selectedGraph = accelerationGraph;
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
    selectedGraph = upperDisplacementGraph;
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
    selectedGraph = lowerDisplacementGraph;
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
    selectedGraph = displacementGraph;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(4);  //index four is the xy graph
    ui->label_7->setText("X,Y Displacement");
    ui->label_8->setText("Max X,Y");
    clearBorder();
    ui->xyLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Upper Displacement");
    ui->label_10->setStyleSheet("QLabel {color :" + displacementGraph->colors[0].name() + "; }");
    ui->label_11->setText("Lower Displacement");
    ui->label_11->setStyleSheet("QLabel {color :" + displacementGraph->colors[1].name() + "; }");
}

void MainWindow::on_rotatButton_clicked()
{
    selectedGraph = rotationGraph;
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(5);  //index five is the rotational location graph
    ui->label_7->setText("Rotational Location");
    ui->label_8->setText("");
    clearBorder();
    ui->rotLabel->setStyleSheet("color: black; font-size: 14px;");

    ui->label_10->setText("Rotational Location");
    ui->label_10->setStyleSheet("QLabel {color :" + rotationGraph->colors[0].name() + "; }");
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
        ui->outputLog->append(QString("Output Recording Started at %1")
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
        ui->outputLog->append(QString("Output Recording Stopped at %1")
                                .arg(QTime::currentTime().toString()));
    }
}


void MainWindow::on_pushButton_ApplySettings_clicked() //when you hit the apply settings button
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    QString password = ui->lineEditPassword->text();
    QString result = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Sha512));

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
        ui->outputLog->append("Configuration changed");
        ui->lineEditPassword->clear();  //clear the password field
        ui->pushButton_ApplySettings->setEnabled(false); //gray the apply button back out
    } else {
        ui->outputLog->append("Wrong password");  //or if you got the password wrong
        ui->maxVel->setText(QString::number(ui->velocitySlider->maximum()));  //change the text back to what it was
        ui->maxAccel->setText(QString::number(ui->accelerationSlider->maximum()));
        ui->eStopKey->setKeySequence(eStopShortcut->shortcut());
    }
}

void MainWindow::on_lineEditPassword_textEdited(const QString &password)
//this function enables the apply button when you type characters into the password field
{
    if (password.isEmpty())
        ui->pushButton_ApplySettings->setEnabled(false);
    else
        ui->pushButton_ApplySettings->setEnabled(true);
}

void MainWindow::on_actionLock_frame_rate_at_30FPS_triggered(bool checked)
{
    if(checked)
    {
        graphRefreshRate = 30;
    }
    else
    {
        graphRefreshRate = 100;
    }

    graphRefreshTimer->setInterval(refreshRateToMS(graphRefreshRate));
}

void MainWindow::on_actionLock_graph_scale_to_max_value_triggered(bool checked)
{

}

// Error Messages

void MainWindow::errorInterafceNotDefined()
{
    ui->errorLog->append(QString("%1: %2").arg(QTime::currentTime().toString(),ERROR_INTERFACE_NOT_SET));
    errorHandler->showMessage(ERROR_INTERFACE_NOT_SET);
}


// Flywheel Operations
void MainWindow::runFlywheelOperations()
{
    flywheelOperation->sync();
}

void MainWindow::startFlywheelInterface()
{
    deviceInterface = interfaceManager->getCurrentInterface();

    if(deviceInterface == NULL)
    {
        errorInterafceNotDefined();
    }
    else
    {
        deviceInterface->startDevice();
        flywheelOperation->setInterface(deviceInterface);
        flywheelRefreshTimer->start();
        ui->outputLog->append(QString("%1: Interface started: %2").arg(QTime::currentTime().toString(),deviceInterface->name()));
    }
}

void MainWindow::stopFlywheelInterface()
{
    if(deviceInterface == NULL)
    {
        errorInterafceNotDefined();
    }
    else
    {
        flywheelRefreshTimer->stop();
        deviceInterface->stopDevice();
        ui->outputLog->append(QString("%1: Interface stopped: %2").arg(QTime::currentTime().toString(),deviceInterface->name()));
    }
}

void MainWindow::closeFlywheelInterface()
{
    if(deviceInterface == NULL)
    {
        errorInterafceNotDefined();
    }
    else
    {
        flywheelOperation->setDefaults();
        flywheelRefreshTimer->stop();
        deviceInterface->stopDevice();

        ui->actionDeviceIndicator->setText(QString("Device: None"));
        ui->outputLog->append(QString("%1: Interface stopped: %2").arg(QTime::currentTime().toString(),deviceInterface->name()));
        ui->outputLog->append(QString("%1: Interface closed: %2").arg(QTime::currentTime().toString(),deviceInterface->name()));

        interfaceManager->closeCurrentInterface();
        deviceInterface = interfaceManager->getCurrentInterface();
    }
}

// Dialog Windows

void MainWindow::openInterfaceSettingsWindow(){  //show the password dialog box
    CommonInterfaceSelector* deviceSettingsWindow = new CommonInterfaceSelector(interfaceManager, this);
    connect(deviceSettingsWindow, SIGNAL(finished(int)), this, SLOT(closeInterfaceSettingsWindow()));
    deviceSettingsWindow->show();
}

void MainWindow::closeInterfaceSettingsWindow()
{
    if (deviceInterface != interfaceManager->getCurrentInterface())
    {
        deviceInterface = interfaceManager->getCurrentInterface();

        if (deviceInterface != NULL)
        {
            ui->actionDeviceIndicator->setText(QString("Device: %1").arg(deviceInterface->name()));
            ui->outputLog->append(QString("%1: Interface set to: %2").arg(QTime::currentTime().toString(),deviceInterface->name()));

            deviceInterface->startDevice();
            ui->outputLog->append(QString("%1: Interface started: %2").arg(QTime::currentTime().toString(),deviceInterface->name()));

            flywheelOperation->setInterface(deviceInterface);
            flywheelRefreshTimer->start();
        }
        else
        {
            ui->actionDeviceIndicator->setText(QString("Device: None"));
        }
    }
}

void MainWindow::on_actionSet_Reset_Password_triggered() //show the password dialog box
{
    SetPasswordDialog* passwordResetWindow = new SetPasswordDialog(this);
    passwordResetWindow->show();
}



