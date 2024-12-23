#include "../include/triangleshape.h"

TriangleShape::TriangleShape(const QColor &color, int thickness)
        : color(color), thickness(thickness) {}

void TriangleShape::draw(QPainter &painter) const {
    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPolygon triangle;
    triangle << startPoint
             << QPoint((startPoint.x() + endPoint.x()) / 2, endPoint.y())
             << QPoint(startPoint.x() - (endPoint.x() - startPoint.x()), endPoint.y());
    painter.drawPolygon(triangle);
}

void TriangleShape::setStartPoint(const QPoint &point) {
    startPoint = point;
}

void TriangleShape::setEndPoint(const QPoint &point){
    endPoint = point;
}