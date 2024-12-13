#include "vertex.h"

Vertex::Vertex(int label) {
    this -> label = label;
    pathFound = false;
    distance = INF;
    parent = nullptr;
    circle = nullptr;
    position = nullptr;
}

QGraphicsEllipseItem* Vertex::getCircle() {
    return circle;
}

QPointF* Vertex::getPosition() {
    return position;
}

int Vertex::getLabel() {
    return label;
}

int Vertex::getDistance() {
    return distance;
}

Vertex* Vertex::getParent() {
    return parent;
}

bool Vertex::getPathFound() {
    return pathFound;
}

QVector<QPair<Vertex*, int>>& Vertex::getNeighbours() {
    return neighbours;
}

void Vertex::setLabel(int label) {
    this -> label = label;
}

void Vertex::setDistance(int distance) {
    this -> distance = distance;
}

void Vertex::setPathFound(int pathFound) {
    this -> pathFound = pathFound;
}
