#pragma once

#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QResizeEvent>
#include <QScreen>

#include <cmath>
#include <iostream>

#include "board.h"

class Gui : public QWidget
{
  public:
    QTimer* timer;
    double t;
    QImage dotImage;
    Gui(Board* _board);
    void paintEvent(QPaintEvent*) override;
    void onUpdate();
    void resizeEvent(QResizeEvent* event);
    Board* board;
    QRect contentArea;
};