#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <vector>
#include <queue>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsEllipseItem* createVertex(QGraphicsScene *scene, const QPointF &position, int radius);
    QGraphicsTextItem* createLabel(QGraphicsScene *scene, const QPointF &position, int radius, const QString &label);
    QGraphicsLineItem* drawEdge(QGraphicsScene *scene, const QPointF &start, const QPointF &end, double weight);
    void initializeGraph();
    void drawGraph(QGraphicsScene *scene);

private slots:
    void onNextPushButtonClicked();

private:
    Ui::MainWindow *ui;
    Graph g;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> heap;
};
#endif // MAINWINDOW_H
