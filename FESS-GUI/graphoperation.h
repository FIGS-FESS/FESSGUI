#ifndef GRAPHHELPER_H
#define GRAPHHELPER_H
#include <qcustomplot.h>

class GraphOperation
{
private:
    QMainWindow* mainWindow;
public:
    QColor measuredColor = QColor(Qt::blue), expectedColor = QColor(Qt::red);
    QColor xColor = QColor(Qt::green), yColor = QColor(Qt::magenta);
    QColor upperColor = QColor(255, 165, 0), lowerColor = QColor(Qt::cyan), rotationalColor = QColor(Qt::black);

    GraphOperation(QMainWindow* mw);
    void SetupRTG(QCustomPlot *rtgwidget, bool isMain, QColor primaryColor, QColor secondaryColor);
    void SetupXYG(QCustomPlot *xygwidget, bool isMain, QColor primaryColor, QColor secondaryColor);
    void addRTGData(QCustomPlot *rtgwidget, double key, double value0, double value1);
};

#endif //GRAPHHELPER_H
