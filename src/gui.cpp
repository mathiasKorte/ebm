#include "gui.h"

#include "mechs.h"

Gui::Gui(Board* _board)
{
    board = _board;

    setWindowTitle("Explorator Belli Mechani");
    setStyleSheet("background-color: black;");
    setMinimumSize(400, 400);
    resize(1000, 1000);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gui::onUpdate);
    timer->start(10);
}

// void Gui::resizeEvent(QResizeEvent* event)
// {
//     // Ensure the content area stays square, based on the current window size
//     int windowWidth = event->size().width();
//     int windowHeight = event->size().height();

//     // Set the side of the square content area to the smaller of width or
//     height int contentSize = std::min(windowWidth, windowHeight);
//     setFixedSize(contentSize, contentSize);  // Keep the window square

//     // Ensure that the content fits within the window size
//     contentArea = QRect(0, 0, contentSize, contentSize);

//     // QWidget::resizeEvent(event);  // Call base class resizeEvent
//     update();
// }

void Gui::resizeEvent(QResizeEvent* event)
{
    // Ensure the content area stays square, based on the current window size
    int windowWidth = event->size().width();
    int windowHeight = event->size().height();

    // Set the side of the square content area to the smaller of width or height
    int contentSize = std::min(windowWidth, windowHeight);

    // Define the content area as a square based on the smaller of the window's
    // width or height
    contentArea = QRect(0, 0, contentSize, contentSize);

    // Optional: Restrict minimum window size if needed
    setMinimumSize(400, 400);  // Uncomment if you want to set a minimum size

    // Optional: Restrict maximum window size if needed
    // setMaximumSize(windowWidth, windowHeight);  // Uncomment if needed

    update();  // Redraw the content
}

void Gui::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    // int width = contentArea.width();
    // int height = contentArea.height();

    painter.translate(contentArea.topLeft());

    int squareSize = std::min(width(), height());
    double scale = ((double)squareSize) / 1000.0;
    painter.setPen(QPen(Qt::white, 5));
    painter.drawRect(0, 0, squareSize, squareSize);

    for (Mech* mech : board->mechs)
    {
        int x = static_cast<int>(mech->x * scale);
        int y = static_cast<int>(mech->y * scale);

        QPoint point(x, y);

        painter.save();
        painter.translate(point);

        double angle = mech->calcTargetAngle();
        painter.rotate(angle);

        int size = static_cast<int>(mech->size * scale);

        QRectF rect(
            -size * 0.95, -size * 0.95, size * 0.95 * 2, size * 0.95 * 2);
        painter.setPen(QPen(Qt::green, 1.5));
        painter.drawArc(rect, 0, 360 * mech->hp / mech->hpMax * 16);
        // painter.setPen(QPen(mech->team == TEAM_RED ? Qt::red :
        // Qt::blue, 1.5));
        painter.setPen(QPen(Qt::white, 1.5));
        painter.drawEllipse(QPoint(0, 0), size, size);

        QFont font = painter.font();
        font.setPixelSize(size * 1.1);
        painter.setFont(font);
        painter.rotate(90);
        QRectF textRect(-size, -size, size * 2, size * 2);
        QRectF textRect2(size / 4, -size / 4 * 3, size, size);
        QRectF textRect3(size / 4, -size / 4 * 1, size, size);

        painter.setPen(QPen(Qt::white, 1));
        painter.drawText(textRect, Qt::AlignCenter, QString::fromStdString(mech->string));

        font.setPixelSize(size * 1.1 / 2);
        painter.setFont(font);
        painter.drawText(
            textRect2, Qt::AlignCenter, QString::number(mech->lvl));
        painter.drawText(textRect3, Qt::AlignCenter, " ");
        painter.restore();
    }
}

void Gui::onUpdate()
{
    t += 1.0;
    board->step();
    update();
}