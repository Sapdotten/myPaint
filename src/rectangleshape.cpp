#include "../include/rectangleshape.h"

RectangleShape::RectangleShape(const QColor &color, int thickness)
    : color(color), thickness(thickness) {
}

void RectangleShape::draw(QPainter &painter) const override {
    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRect(QRect(startPoint, endPoint));
}

void RectangleShape::setStartPoint(const QPoint &point) override {
    startPoint = point;
}

void RectangleShape::setEndPoint(const QPoint &point) override {
    endPoint = point;
}
