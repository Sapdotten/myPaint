#include "../include/rectangleshape.h"

RectangleShape::RectangleShape(const QColor &color, int thickness)
    : color(color), thickness(thickness) {
}

void RectangleShape::draw(QPainter &painter) const {
    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(QRect(startPoint, endPoint));
}

void RectangleShape::setStartPoint(const QPoint &point) {
    startPoint = point;
}

void RectangleShape::setEndPoint(const QPoint &point){
    endPoint = point;
}
