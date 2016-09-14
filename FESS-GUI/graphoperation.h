#ifndef GRAPHHELPER_H
#define GRAPHHELPER_H
#include <qcustomplot.h>

class GraphOperation
{
public:
    GraphOperation(){}
    void SetupRTG(QCustomPlot *rtgwidget, bool isMain);
    void SetupXYG(QCustomPlot *xygwidget, bool isMain);
    void addRTGData(QCustomPlot *rtgwidget, double key, double value0, double value1);
};

#endif //GRAPHHELPER_H
