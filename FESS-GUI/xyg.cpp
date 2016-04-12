#include "xyg.h"

XYG::XYG(QCustomPlot *xygwidget, bool isMain)
{

    xygwidget->addGraph(); // blue dot
    xygwidget->graph(0)->setPen(QPen(Qt::blue));
    xygwidget->graph(0)->setLineStyle(QCPGraph::lsNone);
    xygwidget->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);

    xygwidget->addGraph(); // red dot
    xygwidget->graph(1)->setPen(QPen(Qt::red));
    xygwidget->graph(1)->setLineStyle(QCPGraph::lsNone);
    xygwidget->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);


    // set axes ranges, so we see all data:
    xygwidget->xAxis->setRange(-5, 5);
    xygwidget->yAxis->setRange(-5, 5);

    if(isMain)
    {
        xygwidget->xAxis->setLabel("x");
        xygwidget->yAxis->setLabel("y");
    }
    else
    {
        xygwidget->xAxis->setTickLabels(false);
        xygwidget->yAxis->setTickLabels(false);
    }
}
