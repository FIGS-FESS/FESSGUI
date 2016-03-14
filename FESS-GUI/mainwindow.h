#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QCustomPlot *graphs[];

private slots:


    void on_controlButton_clicked();

    void on_configButton_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_verticalSlider_3_valueChanged(int value);

    void on_actionMetric_triggered();

    void on_actionEmperial_triggered();

    void on_doubleSpinBox_valueChanged(double arg1);

    void realtimeDataSlot();

    void addMainData(double key, double value0, double value1);

    void addAux1Data(double key, double value0, double value1);

    void addAux2Data(double key, double value0, double value1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
