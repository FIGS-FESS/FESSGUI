#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>
#include <qcustomplot.h>
#include "rtg.h"

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
    RTG *mainGraph;
    RTG *velGraph;
    RTG *accGraph;
    QTimer *dataTimer;
    bool playSounds;
    double maxVel;
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

    void addMainData(double key, double value0, double value1);

    void addAux1Data(double key, double value0, double value1);

    void addAux2Data(double key, double value0, double value1);

    void on_pushButton_clicked();

<<<<<<< HEAD
<<<<<<< HEAD
    void on_actionAdjust_Paramaters_triggered();
=======
    void on_spinBox_valueChanged(int arg1);
>>>>>>> refs/remotes/origin/master
=======
    void on_actionDarth_Vader_triggered();

    void on_pushButton_2_clicked();

    void on_actionNone_triggered();

    void on_actionDefault_triggered();

    void keyPressEvent(QKeyEvent *event);
>>>>>>> refs/remotes/origin/master

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
