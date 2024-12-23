#include "../include/circleshape.h"

CircleShape::CircleShape(const QColor &color, int thickness)
    : color(color), thickness(thickness) {
}

void CircleShape::draw(QPainter &painter) const {
    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    int radius = qSqrt(qPow(endPoint.x() - startPoint.x(), 2) +
                       qPow(endPoint.y() - startPoint.y(), 2));
    painter.drawEllipse(startPoint, radius, radius);
}

void CircleShape::setStartPoint(const QPoint &point) {
    startPoint = point;
}

void CircleShape::setEndPoint(const QPoint &point){
    endPoint = point;
}
