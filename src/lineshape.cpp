#include "../include/lineshape.h"

LineShape::LineShape(const QColor &color, int thickness)
    : color(color), thickness(thickness) {
}

void LineShape::draw(QPainter &painter) const {
    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(startPoint, endPoint);
}

void LineShape::setStartPoint(const QPoint &point) {
    startPoint = point;
}

void LineShape::setEndPoint(const QPoint &point){
    endPoint = point;
}
