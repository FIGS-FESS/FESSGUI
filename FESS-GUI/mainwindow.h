#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_horizontalSlider_valueChanged(int value);

    void keyPressEvent(QKeyEvent *);

    void on_dial_valueChanged(int value);

    void on_pushButton_clicked();

    void on_actionAdjust_Paramaters_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
