#include "graphoperation.h"

void GraphOperation::SetupRTG(QCustomPlot *rtgwidget, bool isMain)
{
    rtgwidget->addGraph(); // blue line
    rtgwidget->graph(0)->setPen(QPen(Qt::blue));
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
        rtgwidget->yAxis->setTickLabels(false);
    }
}

void GraphOperation::SetupXYG(QCustomPlot *xygwidget, bool isMain)
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

void GraphOperation::addRTGData(QCustomPlot *rtgwidget, double key, double value0, double value1){
    rtgwidget->graph(0)->addData(key, value0);
    rtgwidget->graph(1)->addData(key, value1);
    // set data of dots:
    rtgwidget->graph(2)->clearData();
    rtgwidget->graph(2)->addData(key, value0);
    rtgwidget->graph(3)->clearData();
    rtgwidget->graph(3)->addData(key, value1);
    // remove data of lines that's outside visible range:
    rtgwidget->graph(0)->removeDataBefore(key-8);
    rtgwidget->graph(1)->removeDataBefore(key-8);
    // rescale value (vertical) axis to fit the current data:
    rtgwidget->graph(0)->rescaleValueAxis();
    rtgwidget->graph(1)->rescaleValueAxis(true);
}
