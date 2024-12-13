#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <vector>
#include <climits>
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QPair>

#define INF INT_MAX

struct compare {
    bool operator() (const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

class Graph
{
public:
    Graph() : V(0) {}
    Graph(int V);

    void initialize(int V);
    void add_edge(int u, int v, int weight);
    void setPosition(int u, int x, int y);
    int getV();
    QVector<QPointF>& getPositions();
    std::vector<std::vector<std::pair<int, int>>>& getAdjacenyList();
    QVector<QGraphicsTextItem*>& getLabels();
    QVector<QGraphicsEllipseItem*>& getVertices();
    QVector<QVector<QPair<int, QGraphicsLineItem*>>>& getEdges();
    std::vector<bool>& getPath_found();
    std::vector<int>& getDistances();
    std::vector<int>& getParents();

private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adjacency_list;
    std::vector<bool> path_found;
    std::vector<int> distances;
    std::vector<int> parents;
    QVector<QPointF> positions;
    QVector<QGraphicsEllipseItem*> vertices;
    QVector<QGraphicsTextItem*> labels;
    QVector<QVector<QPair<int, QGraphicsLineItem*>>> edges;
};

#endif // GRAPH_H
