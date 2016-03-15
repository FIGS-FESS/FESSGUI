#include "rtg.h"

RTG::RTG(QCustomPlot *rtgwidget, bool isMain)
{
    rtgwidget->addGraph(); // blue line
    rtgwidget->graph(0)->setPen(QPen(Qt::blue));
    rtgwidget->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    rtgwidget->graph(0)->setAntialiasedFill(false);
    rtgwidget->addGraph(); // red line
    rtgwidget->graph(1)->setPen(QPen(Qt::red));
    rtgwidget->graph(0)->setChannelFillGraph(rtgwidget->graph(1));

    rtgwidget->addGraph(); // blue dot
    rtgwidget->graph(2)->setPen(QPen(Qt::blue));
    rtgwidget->graph(2)->setLineStyle(QCPGraph::lsNone);
    rtgwidget->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    rtgwidget->addGraph(); // red dot
    rtgwidget->graph(3)->setPen(QPen(Qt::red));
    rtgwidget->graph(3)->setLineStyle(QCPGraph::lsNone);
    rtgwidget->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    if(isMain)
    {
        rtgwidget->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        rtgwidget->xAxis->setDateTimeFormat("hh:mm:ss");
        rtgwidget->xAxis->setAutoTickStep(false);
        rtgwidget->xAxis->setTickStep(2);
        rtgwidget->axisRect()->setupFullAxesBox();
    }
    else
    {
        rtgwidget->xAxis->setTickLabels(false);
    }
    // make left and bottom axes transfer their ranges to right and top axes:
    //connect(rtgwidget->xAxis, SIGNAL(rangeChanged(QCPRange)), rtgwidget->xAxis2, SLOT(setRange(QCPRange)));
    //connect(rtgwidget->yAxis, SIGNAL(rangeChanged(QCPRange)), rtgwidget->yAxis2, SLOT(setRange(QCPRange)));
}

