#pragma once
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QResizeEvent>
#include <QScreen>
#include <QTimer>
#include <QElapsedTimer> 
#include <QWidget>

#include "board.h"
#include "common.h"

/**
 * @brief Visual Interface.
 *
 * Shows the game board and all the Mechs on it. Maybe some Buttons and Labels in the future.
 */
class Gui : public QWidget
{
  public:
    Board* board;
    QTimer* timer = nullptr;
    Mech* focusedMech = nullptr;
    double zoomScale = 1;
    Eigen::Vector2d zoomShift;
    double windowScale = 1;
    Eigen::Vector2d windowShift;
    Eigen::Vector2i windowSize;

    explicit Gui(Board* boardArg);
    ~Gui() override;
    void paintEvent(QPaintEvent* event) override;
    void onUpdate();
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    void calcZoom(bool zoom);
    static double convertAngle(double angle);
    QPoint convertPoint(Eigen::Vector2d vec) const;
    static int int1(double value);
    double getScale() const;
    Eigen::Vector2d getShift() const;
    double distQtMech(QPoint qtPoint, Mech* mech) const;

    void drawLineFromVectors(QPainter& painter,
                             Eigen::Vector2d point1,
                             Eigen::Vector2d point2) const;
    void drawRectFromVectors(QPainter& painter,
                             Eigen::Vector2d point1,
                             Eigen::Vector2d point2) const;

    void drawBoard();
    void drawUnits();
    void drawMechs();
    void drawWeapons();
};