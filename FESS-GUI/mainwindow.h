#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>
#include <qcustomplot.h>
#include <fstream>
#include "rtg.h"
#include "xyg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QMediaPlayer *goplayer;
    QMediaPlayer *stopplayer;
    RTG *mainVelGraph;
    RTG *mainAccGraph;
    RTG *mainUdtGraph;
    RTG *mainLdtGraph;
    XYG *mainXYGraph;
    XYG *mainRotGraph;

    RTG *velGraph;
    RTG *accGraph;
    RTG *updtGraph;
    RTG *lowdtGraph;
    XYG *xyGraph;
    XYG *rotatGraph;

    QTimer *dataTimer;
    bool playSounds = false;
    bool isRecording = false;
    std::ofstream rfs;
    double maxVel = 0;
    double maxAcc = 0;
    double maxUpDt [2] = {0, 0};
    double maxLwDt [2] = {0 ,0};
    enum graph {VEL, ACC, UDT, LDT, XYD, ROT};
    graph mainGraphDisplay = VEL;
    QKeySequence eStopKey;
    QElapsedTimer uptime;
    QAction *eStopShortcut;
    ~MainWindow();

private:
    void transferAxes(QCustomPlot* graph);

private slots:


    void on_controlButton_clicked();

    void on_configButton_clicked();

    void on_velocitySlider_valueChanged(int value);

    void on_accelerationSlider_valueChanged(int value);

    void on_jerkSlider_valueChanged(int value);

    void realtimeDataSlot();

    void addVelocData(double key, double value0, double value1);

    void addAccelData(double key, double value0, double value1);

    void addUpdtData(double key, double x, double y);

    void addLowdtData(double key, double x, double y);

    void addXYData(double ux, double uy, double lx, double ly);

    void addRotatData(double x, double y);

    void on_goButton_clicked();

    void on_actionDarth_Vader_triggered();

    void on_emergencyStopButton_clicked();

    void on_actionNone_triggered();

    void on_actionDefault_triggered();

    void keyPressEvent(QKeyEvent *event);

    void on_velocButton_clicked();

    void on_accelButton_clicked();

    void on_updtButton_clicked();

    void on_lowdtButton_clicked();

    void on_rotatButton_clicked();

    void clearBorder();

    void on_actionStart_Recording_triggered();

    void on_actionStop_Recording_triggered();
	
    void on_performButton_clicked();

    void on_XYButton_clicked();

    void on_pushButton_ApplySettings_clicked();

    void on_actionSet_Reset_Password_triggered();



public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
