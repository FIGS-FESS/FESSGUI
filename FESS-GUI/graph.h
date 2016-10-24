#ifndef GRAPH_H
#define GRAPH_H

#include"qcustomplot.h"
#include <QString>

class Graph
{
protected:
    QCustomPlot *mainPlot, *auxPlot;
public:
    Graph();
    QColor primaryColor, secondaryColor;
};


class ScrollingTimeGraph : public Graph {
public:
    ScrollingTimeGraph(QMainWindow* mainWindow, QCustomPlot* mainPlot, QCustomPlot* auxPlot, QColor primaryColor, QColor secondaryColor, QString yAxisLabel);
    void addData(double time, double primaryData, double secondDaryData);
    void setFill(QColor fillColor);
private:
    void setupPlot(QMainWindow* mainWindow, QCustomPlot *plot, bool isMain, QColor primaryColor, QColor secondaryColor);
    void addData(QCustomPlot* plot, double time, double primaryData, double secondaryData);
};


class LocationGraph : public Graph {
public:
    LocationGraph(QCustomPlot* mainPlot, QCustomPlot* auxPlot, QColor primaryColor, QColor secondaryColor);
    LocationGraph(QCustomPlot* mainPlot, QCustomPlot* auxPlot, QColor primaryColor);
    void addData(double ux, double uy, double lx, double ly);
    void addData(double x, double y);
private:
    void setupPlot(QCustomPlot *plot, bool isMain, QColor primaryColor, QColor secondaryColor);
    void setupPlot(QCustomPlot *plot, bool isMain, QColor primaryColor);
};

#endif // GRAPH_H
