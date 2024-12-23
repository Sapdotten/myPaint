#include "../include/polygonshape.h"

PolygonShape::PolygonShape(const QColor &color, int thickness, int sides)
    : color(color), thickness(thickness), sides(sides) {
}

void PolygonShape::setStartPoint(const QPoint &point) {
    center = point;
}

void PolygonShape::setEndPoint(const QPoint &point) {
    radius = QLineF(center, point).length();
}

void PolygonShape::draw(QPainter &painter) const {
    if (sides < 3 || radius <= 0) return;

    QPolygon polygon;
    for (int i = 0; i < sides; ++i) {
        double angle = 2.0 * M_PI * i / sides;
        QPointF vertex(center.x() + radius * cos(angle), center.y() - radius * sin(angle));
        polygon << vertex.toPoint();
    }

    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawPolygon(polygon);
}
