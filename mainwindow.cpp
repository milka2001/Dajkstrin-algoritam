#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setWindowTitle("Dajkstrin algoritam");

    connect(ui->nextPushButton, &QPushButton::clicked, this, &MainWindow::onNextPushButtonClicked);

    QGraphicsScene *scene = new QGraphicsScene(ui -> graphicsView);
    ui -> graphicsView -> setScene(scene);

    initializeGraph();
    drawGraph(scene);

    std::vector<int>& distances = g.getDistances();
    std::vector<bool>& path_found = g.getPath_found();

    distances[0] = 0;
    heap.push(std::make_pair(0, distances[0]));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNextPushButtonClicked(){
    std::vector<std::vector<std::pair<int, int>>>& adjacency_list = g.getAdjacenyList();
    std::vector<int>& distances = g.getDistances();
    std::vector<bool>& path_found = g.getPath_found();
    std::vector<int>& parents = g.getParents();
    QVector<QGraphicsEllipseItem*>& vertices = g.getVertices();
    QVector<QVector<QPair<int, QGraphicsLineItem*>>>& edges = g.getEdges();

    std::pair<int, int> tmp;
    bool found = false;

    while(!heap.empty()) {
        tmp = heap.top();
        heap.pop();

        if(!path_found[tmp.first]) {
            found = true;
            break;
        }
    }

    if(heap.empty() && found == false) {
        ui -> nextPushButton -> setEnabled(false);
        return;
    }

    //std::cout << tmp.first << " " << vertices.size() << std::endl;
    path_found[tmp.first] = true;

    vertices[tmp.first] -> setBrush(QBrush(QColorConstants::Svg::green));

    if(parents[tmp.first] != -1) {
        for(int i = 0; i < edges[parents[tmp.first]].size(); i ++) {
            if(edges[parents[tmp.first]][i].first == tmp.first) {
                QPen pen(QColorConstants::Svg::firebrick);
                pen.setWidth(3);
                edges[parents[tmp.first]][i].second -> setPen(pen);
            }

        }
    }

    for(const std::pair<int, int> &neighbour : adjacency_list[tmp.first]) {
        if (distances[neighbour.first] > distances[tmp.first] + neighbour.second) {
            distances[neighbour.first] = distances[tmp.first] + neighbour.second;
            heap.push(std::make_pair(neighbour.first, distances[neighbour.first]));
            parents[neighbour.first] = tmp.first;
        }
    }

    if(heap.empty()) {
        ui -> nextPushButton -> setEnabled(false);
        return;
    }

}

QGraphicsEllipseItem* MainWindow::createVertex(QGraphicsScene *scene, const QPointF &position, int radius) {
    QPen pen(Qt::black);
    pen.setWidth(2);
    QGraphicsEllipseItem *vertex = scene->addEllipse(position.x() - radius, position.y() - radius, 2 * radius, 2 * radius,
                                                     pen, QBrush(QColorConstants::Svg::tomato));
    return vertex;
}

QGraphicsTextItem* MainWindow::createLabel(QGraphicsScene *scene, const QPointF &position, int radius, const QString &label) {
    QGraphicsTextItem *text = scene->addText(label);
    text -> setDefaultTextColor(Qt::black);
    text->setPos(position.x() - radius / 2 + 3, position.y() - radius / 2 - 2);

    return text;
}

QGraphicsLineItem* MainWindow::drawEdge(QGraphicsScene *scene, const QPointF &start, const QPointF &end, double weight) {
    double angle = std::atan2(end.y() - start.y(), end.x() - start.x());
    QPointF first(start.x() + std::cos(angle) * 20, start.y() + std::sin(angle) * 20);
    QPointF last(end.x() - std::cos(angle) * 20, end.y() - std::sin(angle) * 20);

    // Draw the main line
    QPen pen(QColorConstants::Svg::limegreen);
    pen.setWidth(3);
    QPointF lineEnd(end.x() - std::cos(angle) * 30, end.y() - std::sin(angle) * 30);
    QGraphicsLineItem *line = scene -> addLine(QLineF(first, lineEnd), pen);

    // Add weight label
    QPointF midPoint = (first + last) / 2;
    midPoint.setX(midPoint.x() - 7);
    QGraphicsTextItem *weightLabel = scene->addText(QString::number(weight));
    weightLabel -> setDefaultTextColor(Qt::black);
    weightLabel->setPos(midPoint);

    // Draw arrowhead
    double arrowSize = 10.0;

    QPointF arrowP1 = last - QPointF(std::cos(angle + M_PI / 6) * arrowSize, std::sin(angle + M_PI / 6) * arrowSize);
    QPointF arrowP2 = last - QPointF(std::cos(angle - M_PI / 6) * arrowSize, std::sin(angle - M_PI / 6) * arrowSize);

    QPolygonF arrowHead;
    arrowHead << last << arrowP1 << arrowP2;
    scene->addPolygon(arrowHead, QPen(Qt::black), QBrush(Qt::black));

    return line;
}

void MainWindow::initializeGraph() {
    g.initialize(9);

    g.setPosition(0, 500, 100);
    g.setPosition(1, 400, 200);
    g.setPosition(2, 300, 300);
    g.setPosition(3, 200, 400);
    g.setPosition(4, 300, 500);
    g.setPosition(5, 400, 400);
    g.setPosition(6, 700, 300);
    g.setPosition(7, 600, 200);
    g.setPosition(8, 500, 300);

    g.add_edge(0, 1, 4);
    g.add_edge(0, 7, 8);
    g.add_edge(1, 7, 11);
    g.add_edge(1, 2, 8);
    g.add_edge(2, 8, 2);
    g.add_edge(2, 3, 7);
    g.add_edge(7, 8, 7);
    g.add_edge(7, 6, 1);
    g.add_edge(8, 6, 6);
    g.add_edge(2, 5, 4);
    g.add_edge(6, 5, 2);
    g.add_edge(3, 5, 14);
    g.add_edge(3, 4, 9);
    g.add_edge(4, 5, 10);
}

void MainWindow::drawGraph(QGraphicsScene *scene) {
    QVector<QPointF>& positions = g.getPositions();
    QVector<QGraphicsEllipseItem*>& vertices = g.getVertices();
    QVector<QGraphicsTextItem*>& labels = g.getLabels();
    QVector<QVector<QPair<int, QGraphicsLineItem*>>>& edges = g.getEdges();

    for(int i = 0; i < g.getV(); i ++) {
        vertices[i] = createVertex(scene, positions[i], 20);
        labels[i] = createLabel(scene, positions[i], 20, QString::number(i));
    }

    std::vector<std::vector<std::pair<int, int>>>& adjacency_list = g.getAdjacenyList();

    for(int i = 0; i < g.getV(); i ++) {
        int n = adjacency_list[i].size();
        for(int j = 0; j < n; j ++) {
            QPair<int, QGraphicsLineItem*> pair(adjacency_list[i][j].first, drawEdge(scene, positions[i], positions[adjacency_list[i][j].first], adjacency_list[i][j].second));
            edges[i].push_back(pair);
        }
    }
}
