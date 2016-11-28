#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "conversions.h"
#include "setpassworddialog.h"
#include "flywheeloperation.h"
#include "commoninterfacemanager.h"
#include "commoninterfaceselector.h"

#include <ctime>

#include <QTime>
#include <QKeyEvent>
#include "qmath.h"

#include <vector>

/*!
 * \brief MainWindow::MainWindow Constructs the MainWindow object.
 * Initializes all variables it needs to. By convention, we initialize values in the constructor
 * rather than in the header/declaraton.
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initMembers();
    setTimers();
    setUpSignals();
    setUpKeyBindings();

    qsrand(time(NULL));

    interfaceManager = new CommonInterfaceManager();
    flywheelOperation = new FlywheelOperation();

    errorHandler = new QErrorMessage(this);
    errorHandler->setWindowTitle("FlyCAM - Error");


    goplayer = new QMediaPlayer(); //sound players
    stopplayer = new QMediaPlayer();

    recording = new RecordingOperation();  //recording values to file

    QSettings settings("settings.ini", QSettings::IniFormat);  //settings file

    if(settings.contains("maxVel")){  //Set max values in slider and spinbox
        maximumVelocity = settings.value("maxVel", "").toInt();
        ui->velocitySpinBox->setMaximum(maximumVelocity);
        ui->velocitySlider->setMaximum(maximumVelocity);
        ui->velocitySlider->setTickInterval(maximumVelocity/sliderTickInterval);
        ui->maxVel->setText(QString::number(maximumVelocity));
    }
    if(settings.contains("maxAcc")){
        maximumAcceleration = settings.value("maxAcc", "").toInt();
        ui->accelerationSpinBox->setMaximum(maximumAcceleration);
        ui->accelerationSlider->setMaximum(maximumAcceleration);
        ui->accelerationSlider->setTickInterval(maximumAcceleration/sliderTickInterval);
        ui->maxAccel->setText(QString::number(maximumAcceleration));
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

/*!
 * \brief MainWindow::initMembers Initializes simple member variables (called by constructor).
 */
void MainWindow::initMembers()
{
    playSounds = false;
    isRecording = false;
    isScaleLocked = false;

    graphRefreshRate = 100;
    flywheelRefreshRate = 200;
    yAxisDisplayBuffer = 1.05; //five percent buffer so we show a little above
    sliderTickInterval = 10;  //how many tick marks on the sliders

    currentExpectedVelocity = RPMtoRadsPerSecond(ui->velocitySpinBox->value());    //initialize expected values based on spinbox values
    currentExpectedAcceleration = ui->accelerationSpinBox->value();
    currentExpectedJerk = ui->jerkSpinBox->value();

    ui->pushButton_ApplySettings->setEnabled(false);  //gray out apply settings button by default
    ui->jerkSlider->setTickInterval(ui->jerkSlider->maximum()/sliderTickInterval);
}

/*!
 * \brief MainWindow::setUpSignals Connects signals to slots (called by constructor).
 */
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

/*!
 * \brief MainWindow::setUpKeyBindings Sets up keyboard shortcuts (called by constructor).
 */
void MainWindow::setUpKeyBindings()
{
    eStopShortcut = new QAction(this);  //setting up the emergency stop shortcut
    addAction(eStopShortcut);
    eStopShortcut->setShortcut(QKeySequence(Qt::Key_Space));

    connect(eStopShortcut, SIGNAL(triggered(bool)), this, SLOT(on_emergencyStopButton_clicked()));

    ui->eStopKey->setKeySequence(eStopShortcut->shortcut()); //E stop shortcut can be user defined
}

/*!
 * \brief MainWindow::setTimers Sets up timers. Connects them to the appropriate slots.
 */
void MainWindow::setTimers()
{
    graphRefreshTimer = new QTimer(this);
    flywheelRefreshTimer = new QTimer(this);

    graphRefreshTimer->setInterval(refreshRateToMS(graphRefreshRate));
    flywheelRefreshTimer->setInterval(refreshRateToMS(flywheelRefreshRate));

    graphRefreshTimer->start(refreshRateToMS(graphRefreshRate));

    connect(graphRefreshTimer, SIGNAL(timeout()), SLOT(realtimeDataSlot()));
    connect(flywheelRefreshTimer, SIGNAL(timeout()), SLOT(runFlywheelOperations()));
}

/*!
 * \brief MainWindow::realtimeDataSlot This runs continuously to update displays, graphs, and recording.
 */
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
    if(isScaleLocked){        
        int velocityHeight = maximumVelocity * yAxisDisplayBuffer;
        int accelerationHeight = maximumAcceleration * yAxisDisplayBuffer;
        velocityGraph->addData(currentTime, actualVelocity, radsPerSecondToRPM(currentExpectedVelocity),velocityHeight);
        accelerationGraph->addData(currentTime, actualAcceleration, currentExpectedAcceleration, accelerationHeight);
    }
    else {
        velocityGraph->addData(currentTime, actualVelocity, radsPerSecondToRPM(currentExpectedVelocity));
        accelerationGraph->addData(currentTime, actualAcceleration, currentExpectedAcceleration);
    }
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

    //don't show if you're not on the performance view
    if(ui->stackedWidget->currentIndex() != 1)
    {
        ui->statusBar->clearMessage();
    }
}

/*!
 * \brief MainWindow::~MainWindow The destructor.
 */
MainWindow::~MainWindow()
{
    delete errorHandler;
    delete graphRefreshTimer;
    delete flywheelRefreshTimer;
    delete flywheelOperation;
    delete interfaceManager;
    delete ui;
}

/*!
 * \brief MainWindow::on_controlButton_clicked Changes the page to the control page.
 */
void MainWindow::on_controlButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);  //this is index zero on the stackedwidget
}

/*!
 * \brief MainWindow::on_performButton_clicked Changes the page to the performance monitor page.
 */
void MainWindow::on_performButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/*!
 * \brief MainWindow::on_configButton_clicked Changes the page to the configuarion page.
 */
void MainWindow::on_configButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/*!
 * \brief MainWindow::on_velocitySlider_valueChanged Sets velocity spinbox value to velocit slider values.
 * This keeps spinboxes and sliders in agreement.
 * \param velocity The new slider value.
 */
void MainWindow::on_velocitySlider_valueChanged(int velocity)
{
    ui->velocitySpinBox->setValue(velocity);
}

/*!
 * \brief MainWindow::on_accelerationSlider_valueChanged Sets acceleration spinbox value to acceleration slider value.
 * This keeps the spinbox and slider in agreement.
 * \param acceleration The new slider value.
 */
void MainWindow::on_accelerationSlider_valueChanged(int acceleration)
{
    ui->accelerationSpinBox->setValue(acceleration);
}

/*!
 * \brief MainWindow::on_jerkSlider_valueChanged Sets jerk spinbox value to the jerk slider value.
 * This keeps the spinbox and slider in agreement.
 * \param jerk The new slider value.
 */
void MainWindow::on_jerkSlider_valueChanged(int jerk)
{
    ui->jerkSpinBox->setValue(jerk);
}

/*!
 * \brief MainWindow::on_velocitySpinBox_valueChanged Sets velocity slider value to the velocity spinbox value.
 * \param velocity The new spinbox value.
 */
void MainWindow::on_velocitySpinBox_valueChanged(double velocity)  //reflect spinboxes value on sliders
{
    ui->velocitySlider->setValue((int)velocity);
}

/*!
 * \brief MainWindow::on_accelerationSpinBox_valueChanged Sets acceleration slider value to the acceleration spinbox value.
 * \param acceleration The new spinbox value.
 */
void MainWindow::on_accelerationSpinBox_valueChanged(double acceleration)
{
    ui->accelerationSlider->setValue((int)acceleration);
}

/*!
 * \brief MainWindow::on_jerkSpinBox_valueChanged Sets jerk slider value to the jerk spinbox value.
 * \param jerk The new spinbox value.
 */
void MainWindow::on_jerkSpinBox_valueChanged(double jerk)
{
    ui->jerkSlider->setValue((int)jerk);
}

/*!
 * \brief MainWindow::on_goButton_clicked Signals flywheel to achieve the set motion.
 */
void MainWindow::on_goButton_clicked()
{
    velocitySlopeTimer->stop();
    accelerationSlopeTimer->stop();

    targetVelocity = RPMtoRadsPerSecond(ui->velocitySpinBox->value());  //get the expected/target values, get velocity in rad/s
    targetAcceleration = ui->accelerationSpinBox->value();
    currentExpectedJerk = ui->jerkSpinBox->value();

    velocitySlopeTimer->start(10); //run every 10ms
    accelerationSlopeTimer->start(10);

    flywheelOperation->setMotion(targetVelocity,targetAcceleration,currentExpectedJerk);

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
                            .arg(ui->velocitySpinBox->value()).arg(targetAcceleration).arg(currentExpectedJerk)
                            .arg(QTime::currentTime().toString()));
}

/*!
 * \brief MainWindow::velocitySlope Manages the expected velocity value.
 * This is called every 10 ms after the go button is clicked, until it reaches the target velocity.
 * It uses the expected acceleration as its slope.
 */
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

/*!
 * \brief MainWindow::accelerationSlope Manages the expected acceleration.
 * This is called every 10 ms after the go button is clicked, until the velocity reaches
 * the target value. It uses the set jerk as its slope.
 */
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

/*!
 * \brief MainWindow::on_emergencyStopButton_clicked Signals the flywheel to stop ASAP.
 */
void MainWindow::on_emergencyStopButton_clicked()
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

    flywheelOperation->emergencyStop();
}

/*!
 * \brief MainWindow::on_actionDarth_Vader_triggered Sets sound options to darth vader sound.
 * Crucial to GUI performance and researcher productivity.
 */
void MainWindow::on_actionDarth_Vader_triggered()
{
    playSounds = true;
    ui->actionNone->setChecked(false);
    ui->actionDefault->setChecked(false);
    goplayer->setMedia(QUrl("qrc:/sounds/sounds/I-am-altering-the-deal.wav"));
    stopplayer->setMedia(QUrl("qrc:/sounds/sounds/Darth_Vader_NO!.wav"));
}

/*!
 * \brief MainWindow::on_actionNone_triggered Sets sound options to no sound.
 */
void MainWindow::on_actionNone_triggered()
{
    playSounds = false;
    stopplayer->stop();
    goplayer->stop();
    ui->actionDarth_Vader->setChecked(false);
    ui->actionDefault->setChecked(false);
}

/*!
 * \brief MainWindow::on_actionDefault_triggered Sets default sound options.
 */
void MainWindow::on_actionDefault_triggered()
{
    playSounds = true;
    ui->actionDarth_Vader->setChecked(false);
    ui->actionNone->setChecked(false);
}

/*!
 * \brief MainWindow::on_velocButton_clicked Sets the focus to the velocity graph.
 * This "button" is the auxiliary velocity plot in the sidebar.
 */
void MainWindow::on_velocButton_clicked()
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

/*!
 * \brief MainWindow::on_accelButton_clicked Sets the focus to the acceleration graph.
 * This "button" is the auxiliary acceleration plot in the sidebar.
 */
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

/*!
 * \brief MainWindow::on_updtButton_clicked Sets the focus to the upper displacement graph.
 * This "button" is the auxiliary upper displacement plot in the sidebar.
 */
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

/*!
 * \brief MainWindow::on_lowdtButton_clicked Sets the focus to the lower displacement graph.
 * This "button" is the auxiliary lower displacement plot in the sidebar.
 */
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

/*!
 * \brief MainWindow::on_XYButton_clicked Sets the focus to the upper/lower displacement location graph.
 * This "button" is the auxiliary displacement location plot in the sidebar.
 */
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

/*!
 * \brief MainWindow::on_rotatButton_clicked Sets the focus to the rotational location graph.
 * This "button" is the auxiliary location plot in the sidebar.
 */
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
/*!
 * \brief MainWindow::clearBorder Resets text styles back to default.
 * This is called before changing the font in the above functions.
 */
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

/*!
 * \brief MainWindow::on_actionStart_Recording_triggered Starts the recording funciton.
 * Triggered when "start recording" is hit in the options.
 */
void MainWindow::on_actionStart_Recording_triggered()
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

/*!
 * \brief MainWindow::on_actionStop_Recording_triggered Stops the recording function.
 * Triggered when "stop recording" is hit.
 */
void MainWindow::on_actionStop_Recording_triggered()
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

/*!
 * \brief MainWindow::on_pushButton_ApplySettings_clicked Applies given settings.
 * This sets values for max velocity, acceleration, and jerk, as well as the emergency stop keyboard shortcut.
 */
void MainWindow::on_pushButton_ApplySettings_clicked()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    QString password = ui->lineEditPassword->text();
    QString result = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Sha512));

    if(passwordMatches(password)){  //if the password is correct
        maximumVelocity = qAbs(ui->maxVel->text().toInt()); //negative numbers get converted to abs value
        maximumAcceleration = qAbs(ui->maxAccel->text().toInt());
        QString newMaxVel = QString::number(maximumVelocity);   //update values
        QString newMaxAcc = QString::number(maximumAcceleration);
        QKeySequence newStopKey = ui->eStopKey->keySequence();

        if(!newMaxVel.isEmpty()){  //change range on input methods
            ui->velocitySpinBox->setMaximum(maximumVelocity);
            ui->velocitySlider->setMaximum(maximumVelocity);
            ui->velocitySlider->setTickInterval(maximumVelocity/sliderTickInterval);
            ui->maxVel->setText(newMaxVel);
            settings.setValue("maxVel", newMaxVel);  //update settings file
        }
        if(!newMaxAcc.isEmpty()){
            ui->accelerationSpinBox->setMaximum(maximumAcceleration);
            ui->accelerationSlider->setMaximum(maximumAcceleration);
            ui->accelerationSlider->setTickInterval(maximumAcceleration/sliderTickInterval);
            ui->maxAccel->setText(newMaxAcc);
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

/*!
 * \brief MainWindow::on_lineEditPassword_textEdited Enables the apply settings button.
 * Occurs when text is entered in the password field.
 * \param password The password entered.
 */
void MainWindow::on_lineEditPassword_textEdited(const QString &password)
{
    if (password.isEmpty())
        ui->pushButton_ApplySettings->setEnabled(false);
    else
        ui->pushButton_ApplySettings->setEnabled(true);
}

/*!
 * \brief MainWindow::on_actionLock_frame_rate_at_30FPS_triggered Locks graph refresh rate.
 * When this is checked, the refresh rate is locked to 30 fps.
 * When this is unchecked, the refresh rate resets to the default 100 fps.
 * \param checked Boolean value denoting whether the graphs should be locked to 30 fps.
 */
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

/*!
 * \brief MainWindow::on_actionLock_graph_scale_to_max_value_triggered Locks/unlocks graph scales to 5% aboce the maximum input values.
 * \param checked True if the graph scales should be checked; false otherwise.
 */
void MainWindow::on_actionLock_graph_scale_to_max_value_triggered(bool checked)
{
    isScaleLocked = checked;
}

// Error Messages

/*!
 * \brief MainWindow::errorInterfaceNotDefined Displays an error for interface not defined.
 */
void MainWindow::errorInterfaceNotDefined()
{
    QString errorMessage = "Invalid Interface: Please select a valid interface.";
    ui->errorLog->append(QString("%1: %2").arg(QTime::currentTime().toString(), errorMessage));
    errorHandler->showMessage(errorMessage);
}


// Flywheel Operations

/*!
 * \brief MainWindow::runFlywheelOperations Syncs the flywheelOperation.
 */
void MainWindow::runFlywheelOperations()
{
    flywheelOperation->sync();
}

/*!
 * \brief MainWindow::startFlywheelInterface Starts the flywheel interface.
 */
void MainWindow::startFlywheelInterface()
{
    deviceInterface = interfaceManager->getCurrentInterface();

    if(deviceInterface == NULL)
    {
        errorInterfaceNotDefined();
    }
    else
    {
        deviceInterface->startDevice();
        flywheelOperation->setInterface(deviceInterface);
        flywheelRefreshTimer->start();
        ui->outputLog->append(QString("%1: Interface started: %2").arg(QTime::currentTime().toString(),deviceInterface->name()));
    }
}

/*!
 * \brief MainWindow::stopFlywheelInterface Stops the flywheel interface.
 */
void MainWindow::stopFlywheelInterface()
{
    if(deviceInterface == NULL)
    {
        errorInterfaceNotDefined();
    }
    else
    {
        flywheelRefreshTimer->stop();
        deviceInterface->stopDevice();
        ui->outputLog->append(QString("%1: Interface stopped: %2").arg(QTime::currentTime().toString(),deviceInterface->name()));
    }
}

/*!
 * \brief MainWindow::closeFlywheelInterface Closes the flywheel interface connection.
 */
void MainWindow::closeFlywheelInterface()
{
    if(deviceInterface == NULL)
    {
        errorInterfaceNotDefined();
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

/*!
 * \brief MainWindow::openInterfaceSettingsWindow Opens the interface settings dialog.
 */
void MainWindow::openInterfaceSettingsWindow()
{
    CommonInterfaceSelector* deviceSettingsWindow = new CommonInterfaceSelector(interfaceManager, this);
    connect(deviceSettingsWindow, SIGNAL(finished(int)), this, SLOT(closeInterfaceSettingsWindow()));
    deviceSettingsWindow->show();
}

/*!
 * \brief MainWindow::closeInterfaceSettingsWindow Closes the interface settings dialog.
 */
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

/*!
 * \brief MainWindow::on_actionSet_Reset_Password_triggered Opens the SetPasswordDialog.
 */
void MainWindow::on_actionSet_Reset_Password_triggered() //show the password dialog box
{
    SetPasswordDialog* passwordResetWindow = new SetPasswordDialog(this);
    passwordResetWindow->show();
}



