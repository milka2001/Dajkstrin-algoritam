#include "graph.h"

Graph::Graph(int V) {
    initialize(V);
}

void Graph::initialize(int V) {
    this -> V = V;
    path_found.resize(V, false);
    adjacency_list.resize(V);
    distances.resize(V, INF);
    parents.resize(V, -1);
    positions.resize(V);
    vertices.resize(V);
    labels.resize(V);
    edges.resize(V);
}

void Graph::add_edge(int u, int v, int weight) {
    adjacency_list[u].push_back(std::make_pair(v, weight));
}

void Graph::setPosition(int u, int x, int y) {
    positions[u].setX(x);
    positions[u].setY(y);
}

int Graph::getV() {
    return V;
}

QVector<QPointF>& Graph::getPositions() {
    return positions;
}

std::vector<std::vector<std::pair<int, int>>>& Graph::getAdjacenyList() {
    return adjacency_list;
}

QVector<QGraphicsEllipseItem*>& Graph::getVertices() {
    return vertices;
}

QVector<QGraphicsTextItem*>& Graph::getLabels() {
    return labels;
}

QVector<QVector<QPair<int, QGraphicsLineItem*>>>& Graph::getEdges() {
    return edges;
}

std::vector<bool>& Graph::getPath_found() {
    return path_found;
}
std::vector<int>& Graph::getDistances() {
    return distances;
}

std::vector<int>& Graph::getParents() {
    return parents;
}
