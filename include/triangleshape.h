#ifndef TRIANGLESHAPE_H
#define TRIANGLESHAPE_H

#include "Shape.h"

class TriangleShape : public Shape {
public:
    TriangleShape(const QColor &color, int thickness)
        : color(color), thickness(thickness) {}

    void draw(QPainter &painter) const override {
        painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        QPolygon triangle;
        triangle << startPoint
                 << QPoint((startPoint.x() + endPoint.x()) / 2, endPoint.y())
                 << QPoint(startPoint.x() - (endPoint.x() - startPoint.x()), endPoint.y());
        painter.drawPolygon(triangle);
    }

    void setStartPoint(const QPoint &point) override {
        startPoint = point;
    }

    void setEndPoint(const QPoint &point) override {
        endPoint = point;
    }

private:
    QPoint startPoint, endPoint;
    QColor color;
    int thickness;
};

#endif // TRIANGLESHAPE_H
