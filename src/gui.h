#pragma once
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QResizeEvent>
#include <QScreen>
#include <QTimer>
#include <QWidget>

#include "board.h"
#include "common.h"

class Gui : public QWidget
{
  public:
    Board* board;
    QTimer* timer;

    Mech* focusedMech = nullptr;
    double zoomScale;
    Eigen::Vector2d zoomShift;
    double windowScale;
    Eigen::Vector2d windowShift;
    Eigen::Vector2d windowSize;

    Gui(Board* _board);
    void paintEvent(QPaintEvent*) override;
    void onUpdate();
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);

    void calcZoom(bool zoom);
    double convAngle(double angle);
    QPoint convPoint(Eigen::Vector2d vec);
    double getScale();
    Eigen::Vector2d getShift();
    double distQtMech(QPoint qt, Mech* mech);

    void drawLineFromVectors(QPainter& painter,
                             Eigen::Vector2d p1,
                             Eigen::Vector2d p2);
    void drawRectFromVectors(QPainter& painter,
                             Eigen::Vector2d p1,
                             Eigen::Vector2d p2);

    void drawBoard();
    void drawUnits();
    void drawMechs();
    void drawWeapons();
};