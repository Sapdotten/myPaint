#include "../include/lineshape.h"

LineShape::LineShape(const QColor &color, int thickness)
    : color(color), thickness(thickness) {
}

void LineShape::draw(QPainter &painter) const override {
    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(startPoint, endPoint);
}

void LineShape::setStartPoint(const QPoint &point) override {
    startPoint = point;
}

void LineShape::setEndPoint(const QPoint &point) override {
    endPoint = point;
}
