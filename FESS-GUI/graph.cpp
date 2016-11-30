#include "graph.h"

/*!
 * \brief Graph::Graph Empty constructor for the base class. This should not be used.
 */
Graph::Graph()
{
}

/*!
 * \brief ScrollingTimeGraph::ScrollingTimeGraph Constructs the ScrollingTimeGraph.
 * \param mainWindow A pointer to the mainWindow, used for connecting ranges of the graph.
 * \param mainPlot The main plot for this graph.
 * \param auxPlot The auxiliary plot for this graph, which lives in the sidebar.
 * \param primaryColor The color of the primary line of this graph.
 * \param secondaryColor The color of the secondary line of this graph.
 * \param displayUnit The units to use in displays.
 * \param numDisplayValues The number of values to display in maxDisplay and currentDisplay.
 */
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

/*!
 * \brief ScrollingTimeGraph::setFill Sets the fill between two lines.
 * \param fillColor The color to set the fill to.
 */
void ScrollingTimeGraph::setFill(QColor fillColor){
    mainPlot->graph(0)->setBrush(QBrush(fillColor));
    auxPlot->graph(0)->setBrush(QBrush(fillColor));
}

/*!
 * \brief ScrollingTimeGraph::setupPlot Sets the plot up according to our standards.
 * \param mainWindow A pointer to the mainWindow, used for setting up a connection.
 * \param plot The plot which is being set up.
 * \param isMain A boolean for whether this is main or not.
 * \param primaryColor The color of the primary line.
 * \param secondaryColor The color of the secondary line.
 */
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

/*!
 * \brief ScrollingTimeGraph::addData Adds two data points to both plots at the given time.
 * \param time The x-axis value for the new points.
 * \param primaryData The y-value of the point to add to the primary line.
 * \param secondaryData The y-value of the point to add to the secondary line.
 * \param maxValue The maximum expected y-value on the graph. If this is set to a negative number,
 *          this is disregarded, and the plots resize dynamically to accomodate real values.
 */
void ScrollingTimeGraph::addData(double time, double primaryData, double secondaryData, int maxValue){
    currentPrimary = primaryData;
    currentSecondary = secondaryData;

    if(primaryData > maxPrimary)
        maxPrimary = primaryData;
    if(secondaryData > maxSecondary)
        maxSecondary = secondaryData;

    addData(mainPlot, time, primaryData, secondaryData, maxValue);
    addData(auxPlot, time, primaryData, secondaryData, maxValue);
}

/*!
 * \brief ScrollingTimeGraph::addData Used by the previous addData to add data to each plot.
 * \param plot The plot to which this adds data.
 * \param time The x-axis value for the new points.
 * \param primaryData The y-value of the point to add to the primary line.
 * \param secondaryData The y-value of the point to add to the secondary line.
 * \param maxValue The maximum expected y-value on the graph. If this is set to a negative number,
 *          this is disregarded, and the plots resize dynamically to accomodate real values.
 */
void ScrollingTimeGraph::addData(QCustomPlot* plot, double time, double primaryData, double secondaryData, int maxValue){
    int range = 8; //this is the width view size of the graph
    plot->graph(0)->addData(time, primaryData);
    plot->graph(1)->addData(time, secondaryData);

    // set data of dots:
    plot->graph(2)->clearData();
    plot->graph(2)->addData(time, primaryData);
    plot->graph(3)->clearData();
    plot->graph(3)->addData(time, secondaryData);

    // remove data of lines that's outside visible range:
    plot->graph(0)->removeDataBefore(time-range);
    plot->graph(1)->removeDataBefore(time-range);

    // rescale value (vertical) axis to fit the current data:
    if(maxValue < 0){
        plot->graph(0)->rescaleValueAxis();
        plot->graph(1)->rescaleValueAxis(true);
    }
    else{
        plot->yAxis->setRange(0, maxValue);

    }

    // make currentTime axis range scroll with the data (at a constant range size of 8)
    plot->xAxis->setRange(time+0.25, range, Qt::AlignRight);
    plot->replot();
}

/*!
 * \brief ScrollingTimeGraph::maxDisplay Returns a string showing the maximum values seen by this graph so far,
 *          with units.
 * \return The string which contains the maximum values seen by this graph.
 */
QString ScrollingTimeGraph::maxDisplay(){
    QString ret = QString::number(maxPrimary);
    if (numDisplayValues >= 2)
        ret += ", " + QString::number(maxSecondary, 'f', 4);
    return ret + " " + displayUnit;
}

/*!
 * \brief ScrollingTimeGraph::currentDisplay Returns a string showing the most recent values seen by this graph.
 *          with units.
 * \return The string which contains the most recent values seen by this graph.
 */
QString ScrollingTimeGraph::currentDisplay(){
    QString ret = QString::number(currentPrimary);
    if (numDisplayValues >= 2)
        ret += ", " + QString::number(currentSecondary, 'f', 4);
    return ret + " " + displayUnit;
}


/*********************************** Location Graph functions **************************************/
/*!
 * \brief LocationGraph::LocationGraph Constructs a LocationGraph
 * \param mainPlot The main plot for this graph.
 * \param auxPlot The auxiliary plot for this graph, which lives in the sidebar.
 * \param colors A vector of the colors to be given to the points in this graph.
 * \param displayUnit A string containing the name of the units to use in this graph's displays.
 * \param numPoints The number of points to display on this graph.
 */
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

/*!
 * \brief LocationGraph::setupPlot Sets up a plot for this graph.
 * \param plot The plot to set up.
 * \param isMain A boolean value indicating if this plot is the main.
 * \param colors The vector of colors to attribute to this plot.
 * \param numPoints The number of points this graph will have.
 */
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

/*!
 * \brief LocationGraph::addData Adds a vector of points to the graph.
 * \param points The points to add to this graph.
 */
void LocationGraph::addData(std::vector<QPointF> points)
{
    for(int i = 0; i <  (int)points.size() && i < numPoints; i++){
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

/*!
 * \brief LocationGraph::maxDisplay Returns a display of the maximum value seen by this graph so far,
 *          with units.
 * \return A string containing the maximum values seen by this graph so far.
 */
QString LocationGraph::maxDisplay(){
    QString ret = "(" + QString::number(maxPoints[0].x(), 'f', 4) + ", " + QString::number(maxPoints[0].y(), 'f', 4) + ")";

    for(int i = 1; i < numPoints; i++){
        ret += ", (" + QString::number(maxPoints[i].x(), 'f', 4) + ", " + QString::number(maxPoints[i].y(), 'f', 4) + ")";
    }

    return ret + " " + displayUnit;
}

/*!
 * \brief LocationGraph::currentDisplay Returns a display of the most recent values seen by this graph,
 *          with units.
 * \return A string containing the most recent values seen by this graph.
 */
QString LocationGraph::currentDisplay(){
    QString ret = "(" + QString::number(currentPoints[0].x(), 'f', 4) + ", " + QString::number(currentPoints[0].y(), 'f', 4) + ")";

    for(int i = 1; i < numPoints; i++){
        ret += ", (" + QString::number(currentPoints[i].x(), 'f', 4) + ", " + QString::number(currentPoints[i].y(), 'f', 4) + ")";
    }

    return ret + " " + displayUnit;
}
