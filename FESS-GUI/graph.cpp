#include "graph.h"

Graph::Graph()
{

}

ScrollingTimeGraph::ScrollingTimeGraph(QMainWindow* mainWindow, QCustomPlot* mainPlot, QCustomPlot* auxPlot,
                                       QColor primaryColor, QColor secondaryColor, QString displayUnit, int numDisplayValues){
    this->mainPlot = mainPlot;
    this->auxPlot = auxPlot;
    this->primaryColor = primaryColor;
    this->secondaryColor = secondaryColor;
    this->displayUnit = displayUnit;
    this->numDisplayValues = numDisplayValues;

    setupPlot(mainWindow, mainPlot, true, primaryColor, secondaryColor);
    mainPlot->yAxis->setLabel(displayUnit);
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
    currentPrimary = primaryData;
    currentSecondary = secondaryData;

    if(primaryData > maxPrimary)
        maxPrimary = primaryData;
    if(secondaryData > maxSecondary)
        maxSecondary = secondaryData;

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

QString ScrollingTimeGraph::maxDisplay(){
    QString ret = QString::number(maxPrimary);
    if (numDisplayValues >= 1)
        ret += ", " + QString::number(maxSecondary);
    return ret + " " + displayUnit;
}

QString ScrollingTimeGraph::currentDisplay(){
    QString ret = QString::number(currentPrimary);
    if (numDisplayValues >= 1)
        ret += ", " + QString::number(currentSecondary);
    return ret + " " + displayUnit;
}


/*********************************************************************************************/

LocationGraph::LocationGraph(QCustomPlot* mainPlot, QCustomPlot* auxPlot, std::vector<QColor> colors, QString displayUnit, int numPoints){
    this->mainPlot = mainPlot;
    this->auxPlot = auxPlot;
    this->colors = colors;
    this->displayUnit = displayUnit;
    this->numPoints = numPoints;
    maxPoints = std::vector<QPointF> (numPoints, QPointF(std::numeric_limits<qreal>::min(), std::numeric_limits<qreal>::min()));
    currentPoints = std::vector<QPointF> (numPoints);

    setupPlot(mainPlot, true, colors, numPoints);
    setupPlot(auxPlot, false, colors, numPoints);
}


void LocationGraph::setupPlot(QCustomPlot *plot, bool isMain, std::vector<QColor> colors, int numPoints)
{
    for(int i = 0; i < numPoints; i++){
        plot->addGraph(); // blue dot
        plot->graph(i)->setPen(QPen(colors[i]));
        plot->graph(i)->setLineStyle(QCPGraph::lsNone);
        plot->graph(i)->setScatterStyle(QCPScatterStyle::ssDisc);
    }

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
    for(int i = 0; i < points.size() && i < numPoints; i++){
        currentPoints[i] = points[i];
        if(points[i].manhattanLength() > maxPoints[i].manhattanLength())
            maxPoints[i] = points[i];

        mainPlot->graph(i)->clearData();
        mainPlot->graph(i)->addData(points[i].x(), points[i].y());

        auxPlot->graph(i)->clearData();
        auxPlot->graph(i)->addData(points[i].x(), points[i].y());
    }

    mainPlot->replot();
    auxPlot->replot();
}


QString LocationGraph::maxDisplay(){
    QString ret = "(" + QString::number(maxPoints[0].x()) + ", " + QString::number(maxPoints[0].y()) + ")";

    for(int i = 1; i < numPoints; i++){
        ret += ", (" + QString::number(maxPoints[i].x()) + ", " + QString::number(maxPoints[i].y()) + ")";
    }

    return ret + " " + displayUnit;
}

QString LocationGraph::currentDisplay(){
    QString ret = "(" + QString::number(currentPoints[0].x()) + ", " + QString::number(currentPoints[0].y()) + ")";

    for(int i = 1; i < numPoints; i++){
        ret += ", (" + QString::number(currentPoints[i].x()) + ", " + QString::number(currentPoints[i].y()) + ")";
    }

    return ret + " " + displayUnit;
}
