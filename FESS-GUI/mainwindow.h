#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>
#include <qcustomplot.h>
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
    XYG *mainUdtGraph;
    XYG *mainLdtGraph;
    XYG *mainRotGraph;
    RTG *velGraph;
    RTG *accGraph;
    XYG *updtGraph;
    XYG *lowdtGraph;
    XYG *rotatGraph;
    QTimer *dataTimer;
    bool playSounds;
    double maxVel;
    double maxAcc;
    enum graph {VEL, ACC, UDT, LDT, ROT};
    graph mainGraphDisplay;
    ~MainWindow();

private slots:


    void on_controlButton_clicked();

    void on_configButton_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_verticalSlider_3_valueChanged(int value);

    void on_actionMetric_triggered();

    void on_actionEmperial_triggered();

    void realtimeDataSlot();

    void addVelocData(double key, double value0, double value1);

    void addAccelData(double key, double value0, double value1);

    void addUpdtData(double x, double y);

    void addLowdtData(double x, double y);

    void addRotatData(double x, double y);

    void on_pushButton_clicked();

    void on_actionDarth_Vader_triggered();

    void on_pushButton_2_clicked();

    void on_actionNone_triggered();

    void on_actionDefault_triggered();

    void keyPressEvent(QKeyEvent *event);

    void on_velocButton_clicked();

    void on_accelButton_clicked();

    void on_updtButton_clicked();

    void on_lowdtButton_clicked();

    void on_rotatButton_clicked();

    void clearBorder();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
