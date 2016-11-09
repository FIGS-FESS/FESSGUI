// QT Libraries
#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QSpinBox>

// Custom Libraries
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
