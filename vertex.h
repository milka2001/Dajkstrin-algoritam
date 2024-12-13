#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QVector>
#include <climits>

#define INF INT_MAX

class Vertex
{
public:
    Vertex(int label);
    QGraphicsEllipseItem getCircle();
    QPointF getPosition();
    int getLabel();
    int getDistance();
    Vertex* getParent();
    bool getPathFound();
    QVector<QPair<Vertex*, int>>& getNeighbours();
    void setLabel(int label);
    void setDistance(int distance);
    void setPathFound(int pathFound);


private:
    QGraphicsEllipseItem circle;
    QPointF position;
    int label;
    int distance;
    Vertex* parent;
    bool pathFound;
    QVector<QPair<Vertex*, int>> neighbours;
};

#endif // VERTEX_H
