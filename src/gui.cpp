#include "gui.h"

#include "mechs/meltingpoint.h"

constexpr double BOARD_X = 72;
constexpr double BOARD_Y = 60;
constexpr double BOARD_SIDE = 6;
constexpr double ZOOM_BOARDER = 2;

Gui::Gui(Board* boardArg)
    : board(boardArg)
    , timer(new QTimer(this))
{
    setWindowTitle("Explorator Belli Mechani");
    setStyleSheet("background-color: black;");
    setMinimumSize(100, int1(100 * BOARD_Y / BOARD_X));
    resize(1500, int1(1500 * BOARD_Y / BOARD_X));

    connect(timer, &QTimer::timeout, this, &Gui::onUpdate);
    timer->start(100);
}

Gui::~Gui()
{
    delete timer;
}

void Gui::onUpdate()
{
    const bool timing = (board->t % 10 == 0);
    QElapsedTimer timerFPS;
    if (timing)
        timerFPS.start();

    board->step();
    update();

    if (timing)
    {
        const qint64 elapsed = timerFPS.elapsed();
        qDebug() << "onUpdate execution time:" << elapsed << "ms";
    }

    if (board->t == 100)
    {
        close();
        QApplication::quit();
    }
}

void Gui::resizeEvent(QResizeEvent* event)
{
    const double windowWidth = static_cast<double>(event->size().width());
    const double windowHeight = static_cast<double>(event->size().height());

    windowScale = std::min(windowWidth / BOARD_X, windowHeight / BOARD_Y);
    windowSize = (Eigen::Vector2d(BOARD_X, BOARD_Y) * windowScale).cast<int>();
    windowShift = -Eigen::Vector2d(0, 0);

    update();
}

double Gui::distQtMech(QPoint qtPoint, Mech* mech) const
{
    if (mech == nullptr)
        return std::numeric_limits<double>::max();

    const QPoint delta = convertPoint(mech->position) - qtPoint;
    return std::sqrt((delta.x() * delta.x()) + (delta.y() * delta.y()));
}

void Gui::mousePressEvent(QMouseEvent* event)
{
    const QPoint mousePos = event->pos();
    focusedMech = nullptr;

    for (Mech* mech : board->mechs)
        if (distQtMech(mousePos, mech) < distQtMech(mousePos, focusedMech))
            focusedMech = mech;

    update();
}

double Gui::convertAngle(double angle)
{
    return angle * 360.0 / (2.0 * PI);
}

int Gui::int1(double value)
{
    int mapped = static_cast<int>(value);
    if (mapped == 0)
        mapped++;
    return mapped;
}

QPoint Gui::convertPoint(Eigen::Vector2d vec) const
{
    vec += getShift();
    vec *= getScale();
    vec = clampVector(vec, Eigen::Vector2d(0, 0), windowSize.cast<double>());
    return {static_cast<int>(vec.x()), static_cast<int>(vec.y())};
}

double Gui::getScale() const
{
    return zoomScale * windowScale;
}
Eigen::Vector2d Gui::getShift() const
{
    return zoomShift + windowShift;
}

void Gui::paintEvent(QPaintEvent*)
{
    calcZoom(/*zoom=*/true);
    drawBoard();
    // drawUnits();
    drawWeapons();
    drawMechs();
}

void Gui::calcZoom(bool zoom)
{
    if (zoom)
    {
        double minX = std::numeric_limits<double>::max();
        double maxX = std::numeric_limits<double>::lowest();
        double minY = std::numeric_limits<double>::max();
        double maxY = std::numeric_limits<double>::lowest();

        for (Mech* mech : board->mechs)
        {
            const double size = mech->getRadius() + ZOOM_BOARDER;

            minX = std::min(minX, mech->position.x() - size);
            maxX = std::max(maxX, mech->position.x() + size);
            minY = std::min(minY, mech->position.y() - size);
            maxY = std::max(maxY, mech->position.y() + size);
        }

        zoomScale = std::min(BOARD_X / (maxX - minX), BOARD_Y / (maxY - minY));
        zoomShift = -Eigen::Vector2d(minX, minY);
    } else
    {
        zoomScale = 1.0;
        zoomShift = Eigen::Vector2d(0, 0);
    }
}

void Gui::drawLineFromVectors(QPainter& painter,
                              Eigen::Vector2d point1,
                              Eigen::Vector2d point2) const
{
    const QPoint qoint1 = convertPoint(point1);
    const QPoint qoint2 = convertPoint(point2);
    painter.drawLine(qoint1.x(), qoint1.y(), qoint2.x(), qoint2.y());
}

void Gui::drawRectFromVectors(QPainter& painter,
                              Eigen::Vector2d point1,
                              Eigen::Vector2d point2) const
{
    drawLineFromVectors(painter, point1, Eigen::Vector2d(point1.x(), point2.y()));
    drawLineFromVectors(painter, Eigen::Vector2d(point1.x(), point2.y()), point2);
    drawLineFromVectors(painter, point2, Eigen::Vector2d(point2.x(), point1.y()));
    drawLineFromVectors(painter, Eigen::Vector2d(point2.x(), point1.y()), point1);
}

void Gui::drawBoard()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 5));

    painter.drawRect(0, 0, windowSize.x(), windowSize.y());
    drawRectFromVectors(painter, Eigen::Vector2d(0, 0), Eigen::Vector2d(BOARD_X, BOARD_Y));

    painter.setPen(QPen(Qt::white, 1));
    drawLineFromVectors(
        painter, Eigen::Vector2d(0, BOARD_Y * 0.5), Eigen::Vector2d(BOARD_X, BOARD_Y * 0.5));
    drawLineFromVectors(
        painter, Eigen::Vector2d(BOARD_SIDE, 0), Eigen::Vector2d(BOARD_SIDE, BOARD_Y));
    drawLineFromVectors(painter,
                        Eigen::Vector2d(BOARD_X - BOARD_SIDE, 0),
                        Eigen::Vector2d(BOARD_X - BOARD_SIDE, BOARD_Y));

    painter.setPen(QPen(Qt::darkGray, 1));
    for (int i = 0; i < BOARD_X; i++)
        drawLineFromVectors(painter, Eigen::Vector2d(i, 0), Eigen::Vector2d(i, BOARD_Y));
    for (int i = 0; i < BOARD_Y; i++)
        drawLineFromVectors(painter, Eigen::Vector2d(0, i), Eigen::Vector2d(BOARD_X, i));
}

void Gui::drawUnits()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 1));

    for (Unit* unit : board->units)
        drawRectFromVectors(painter,
                            unit->position.cast<double>(),
                            (unit->position + unit->getSize()).cast<double>());
}

void Gui::drawMechs()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 1));

    for (Mech* mech : board->mechs)
    {
        const QPoint point = convertPoint(mech->position);

        painter.save();
        painter.translate(point);

        painter.rotate(convertAngle(mech->angle));

        const double size = mech->getRadius() * getScale();

        painter.drawEllipse(QPoint(0, 0), int1(size), int1(size));

        const QRectF rect(-size * 0.97, -size * 0.97, size * 0.97 * 2, size * 0.97 * 2);
        painter.setPen(QPen(mech->team == Team::red ? Qt::red : Qt::green, 5.0));
        if (focusedMech != nullptr)
            for (Weapon* weapon : focusedMech->weapons)
                if (mech == weapon->target)
                    painter.setPen(QPen(mech->team == Team::red ? Qt::red : Qt::green, 5));
        painter.drawArc(rect, 0, int1(360 * mech->hp / mech->hpMax * 16));
        painter.setPen(QPen(Qt::white, 2.0));

        painter.drawEllipse(QPoint(0, 0), int1(size), int1(size));

        QFont font = painter.font();
        font.setPixelSize(int1(size * (1.0 + static_cast<int>(mech->getString().size() == 1))));
        font.setStretch(QFont::Condensed);
        painter.setFont(font);
        painter.rotate(90);

        const QRectF textRect(-size, -size, size * 2, size * 2);
        const QRectF textRect2(size / 4 * 0, -size / 4 * 3, size, size);
        const QRectF textRect3(size / 4 * 0, -size / 4 * 1, size, size);

        painter.setPen(QPen(Qt::white, 1));
        painter.drawText(textRect, Qt::AlignCenter, QString::fromStdString(mech->getString()));

        font.setPixelSize(
            int1(size * (1.0 + static_cast<int>(mech->getString().size() == 1)) / 2.0));
        font.setStretch(QFont::Condensed);
        painter.setFont(font);
        if (mech->lvl != 1)
            painter.drawText(textRect2, Qt::AlignCenter, QString::number(mech->lvl));
        painter.drawText(textRect3, Qt::AlignCenter, " ");

        painter.restore();
    }
}

void Gui::drawWeapons()
{
    QPolygonF triangleBase;
    triangleBase << QPointF(0, -1) << QPointF(-qSin(PI / 3) / 2.0, qCos(PI / 3) / 2.0)
                 << QPointF(qSin(PI / 3) / 2.0, qCos(PI / 3) / 2.0);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 1));
    painter.setClipRect(QRect(0, 0, windowSize.x(), windowSize.y()));
    // painter.setBrush(Qt::darkGray);

    for (Mech* mech : board->mechs)
    {
        QTransform transform;
        transform.scale(getScale() / 2.0 * mech->getRadius(), getScale() / 2.0 * mech->getRadius());
        const QPolygonF triangle = transform.map(triangleBase);

        for (Weapon* weapon : mech->weapons)
        {
            if ((dynamic_cast<LaserWeapon*>(weapon) != nullptr) && (weapon->target != nullptr)
                && weapon->inTargetRange())
            {
                painter.save();
                painter.setPen(QPen(QColor("turquoise"), 3));
                drawLineFromVectors(painter, weapon->getPosition(), weapon->target->position);
                painter.restore();
            }
            if (dynamic_cast<MeltingPointSpawnerWeapon*>(weapon) == nullptr)
            {
                const QPoint point = convertPoint(weapon->getPosition());

                painter.save();
                painter.translate(point);
                painter.rotate(convertAngle(weapon->angle) + 90);

                painter.drawPolygon(triangle);
                painter.restore();

                if (mech == focusedMech)
                {
                    painter.save();
                    painter.translate(point);
                    painter.rotate(convertAngle(normalizeAngle(mech->angle + weapon->relAngle)));

                    const double range = weapon->getRange() * getScale();

                    const QRectF rect(-range, -range, range * 2, range * 2);

                    const int angle = static_cast<int>(convertAngle(weapon->getAngleSize()));
                    painter.drawArc(rect, -angle * 16, angle * 2 * 16);

                    if (weapon->getAngleSize() < PI)
                    {
                        painter.drawLine(QPointF(0, 0),
                                         QPointF(range * cos(qDegreesToRadians(-angle)),
                                                 range * sin(qDegreesToRadians(-angle))));
                        painter.drawLine(QPointF(0, 0),
                                         QPointF(range * cos(qDegreesToRadians(angle)),
                                                 range * sin(qDegreesToRadians(angle))));
                    }

                    painter.restore();
                }
            }
        }
    }
}