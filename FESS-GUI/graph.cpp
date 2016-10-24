#include "graph.h"

Graph::Graph()
{

}

ScrollingTimeGraph::ScrollingTimeGraph(QMainWindow* mainWindow, QCustomPlot* mainPlot, QCustomPlot* auxPlot,
                                       QColor primaryColor, QColor secondaryColor, QString yAxisLabel){
    this->mainPlot = mainPlot;
    this->auxPlot = auxPlot;
    this->primaryColor = primaryColor;
    this->secondaryColor = secondaryColor;

    setupPlot(mainWindow, mainPlot, true, primaryColor, secondaryColor);
    mainPlot->yAxis->setLabel(yAxisLabel);
    setupPlot(mainWindow, auxPlot, false, primaryColor, secondaryColor);
}

void ScrollingTimeGraph::setFill(QColor fillColor){
    mainPlot->graph(0)->setBrush(QBrush(fillColor));
    auxPlot->graph(0)->setBrush(QBrush(fillColor));
}

void ScrollingTimeGraph::setupPlot(QMainWindow* mainWindow, QCustomPlot *plot, bool isMain, QColor primaryColor, QColor secondaryColor)
{
    plot->addGraph(); // primary line
    plot->graph(0)->setPen(QPen(primaryColor));
    plot->graph(0)->setAntialiasedFill(false);
    plot->addGraph(); // secondary line
    plot->graph(1)->setPen(QPen(secondaryColor));
    plot->graph(0)->setChannelFillGraph(plot->graph(1));

    plot->addGraph(); // primary dot
    plot->graph(2)->setPen(QPen(primaryColor));
    plot->graph(2)->setLineStyle(QCPGraph::lsNone);
    plot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    plot->addGraph(); // secondary dot
    plot->graph(3)->setPen(QPen(secondaryColor));
    plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    plot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    if(isMain)
    {
        plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        plot->xAxis->setDateTimeFormat("hh:mm:ss");
        plot->xAxis->setAutoTickStep(false);
        plot->xAxis->setTickStep(2);
        plot->axisRect()->setupFullAxesBox();
        // make left and bottom axes transfer their ranges to right and top axes:
        mainWindow->connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
        mainWindow->connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));
    }
    else
    {
        plot->xAxis->setTickLabels(false);
        plot->yAxis->setTickLabels(false);
    }
}

void ScrollingTimeGraph::addData(double time, double primaryData, double secondaryData){
    addData(mainPlot, time, primaryData, secondaryData);
    addData(auxPlot, time, primaryData, secondaryData);
}

void ScrollingTimeGraph::addData(QCustomPlot* plot, double time, double primaryData, double secondaryData){
    plot->graph(0)->addData(time, primaryData);
    plot->graph(1)->addData(time, secondaryData);

    // set data of dots:
    plot->graph(2)->clearData();
    plot->graph(2)->addData(time, primaryData);
    plot->graph(3)->clearData();
    plot->graph(3)->addData(time, secondaryData);

    // remove data of lines that's outside visible range:
    plot->graph(0)->removeDataBefore(time-8);
    plot->graph(1)->removeDataBefore(time-8);

    // rescale value (vertical) axis to fit the current data:
    plot->graph(0)->rescaleValueAxis();
    plot->graph(1)->rescaleValueAxis(true);

    // make currentTime axis range scroll with the data (at a constant range size of 8)
    plot->xAxis->setRange(time+0.25, 8, Qt::AlignRight);
    plot->replot();
}


LocationGraph::LocationGraph(QCustomPlot* mainPlot, QCustomPlot* auxPlot, QColor primaryColor, QColor secondaryColor){
    this->mainPlot = mainPlot;
    this->auxPlot = auxPlot;
    this->primaryColor = primaryColor;
    this->secondaryColor = secondaryColor;
    setupPlot(mainPlot, true, primaryColor, secondaryColor);
    setupPlot(auxPlot, false, primaryColor, secondaryColor);
}

LocationGraph::LocationGraph(QCustomPlot* mainPlot, QCustomPlot* auxPlot, QColor primaryColor){
    this->mainPlot = mainPlot;
    this->auxPlot = auxPlot;
    this->primaryColor = primaryColor;
    setupPlot(mainPlot, true, primaryColor);
    setupPlot(auxPlot, false, primaryColor);
}

void LocationGraph::setupPlot(QCustomPlot *plot, bool isMain, QColor primaryColor, QColor secondaryColor)
{

    plot->addGraph(); // blue dot
    plot->graph(0)->setPen(QPen(primaryColor));
    plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);

    plot->addGraph(); // red dot
    plot->graph(1)->setPen(QPen(secondaryColor));
    plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    plot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

    // set axes ranges, so we see all data:
    plot->xAxis->setRange(-5, 5);
    plot->yAxis->setRange(-5, 5);

    if(isMain)
    {
        plot->xAxis->setLabel("x");
        plot->yAxis->setLabel("y");
    }
    else
    {
        plot->xAxis->setTickLabels(false);
        plot->yAxis->setTickLabels(false);
    }
}

void LocationGraph::setupPlot(QCustomPlot *plot, bool isMain, QColor primaryColor)
{

    plot->addGraph(); // main dot
    plot->graph(0)->setPen(QPen(primaryColor));
    plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);

    // set axes ranges, so we see all data:
    plot->xAxis->setRange(-5, 5);
    plot->yAxis->setRange(-5, 5);

    if(isMain)
    {
        plot->xAxis->setLabel("x");
        plot->yAxis->setLabel("y");
    }
    else
    {
        plot->xAxis->setTickLabels(false);
        plot->yAxis->setTickLabels(false);
    }
}

void LocationGraph::addData(std::vector<QPointF> points)  //function to add xy data to graphs
{
    for(int i = 0; i < points.size(); i++){
        mainPlot->graph(i)->clearData();
        mainPlot->graph(i)->addData(points[i].x(), points[i].y());

        auxPlot->graph(i)->clearData();
        auxPlot->graph(i)->addData(points[i].x(), points[i].y());
    }

    mainPlot->replot();
    auxPlot->replot();
}
