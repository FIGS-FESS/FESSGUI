
#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QSpinBox>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
