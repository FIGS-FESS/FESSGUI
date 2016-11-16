#ifndef GRAPH_H
#define GRAPH_H

#include"qcustomplot.h"
#include <vector>
#include <QString>
#include <QPointF>

/*!
 * \brief The Graph class, base class for all graphs.
 * Each graph contains a main plot (the large graph that is seen when a graph is selected)
 * and a auxiliary plot (the smaller graph that is always visible on the right side).
 */
class Graph
{
protected:
    QCustomPlot *mainPlot, *auxPlot;
    QString displayUnit;
public:
    Graph();
    QColor primaryColor, secondaryColor;
    virtual QString maxDisplay(){return "";}
    virtual QString currentDisplay(){return "";}
};

/*!
 * \brief The ScrollingTimeGraph class, which inherits from the Graph class.
 * This represents a graph with time as the x axis, that "scrolls" with time, showing a sliding window of values.
 * The y axis represents whatever value this graph displays.
 */
class ScrollingTimeGraph : public Graph {
public:
    ScrollingTimeGraph(QMainWindow* mainWindow, QCustomPlot* mainPlot, QCustomPlot* auxPlot, QColor primaryColor, QColor secondaryColor, QString displayUnit, int numDisplayValues);
    void addData(double time, double primaryData, double secondDaryData, int maxValue = -1);
    void setFill(QColor fillColor);
    QString maxDisplay() override;
    QString currentDisplay() override;
private:
    double maxPrimary, maxSecondary, currentPrimary, currentSecondary;
    int numDisplayValues;
    void setupPlot(QMainWindow* mainWindow, QCustomPlot *plot, bool isMain, QColor primaryColor, QColor secondaryColor);
    void addData(QCustomPlot* plot, double time, double primaryData, double secondaryData, int maxValue);
};

/*!
 * \brief The LocationGraph class, which inherits from the Graph class.
 * This represents a graph where the x and y axes represent location.
 * This is a real-time graph, with no view of what happened in the past.
 */
class LocationGraph : public Graph {
public:
    LocationGraph(QCustomPlot* mainPlot, QCustomPlot* auxPlot, std::vector<QColor> colors, QString displayUnit, int numPoints);
    void addData(std::vector<QPointF> points);
    QString maxDisplay() override;
    QString currentDisplay() override;
    std::vector<QColor> colors;
private:
    int numPoints;
    std::vector<QPointF> maxPoints, currentPoints;
    void setupPlot(QCustomPlot *plot, bool isMain, std::vector<QColor> colors, int numPoints);
};

#endif // GRAPH_H
