#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

#include "Shape.h"

class CircleShape : public Shape {
public:
    CircleShape(const QColor &color, int thickness)
        : color(color), thickness(thickness) {}

    void draw(QPainter &painter) const override {
        painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        int radius = qSqrt(qPow(endPoint.x() - startPoint.x(), 2) +
                           qPow(endPoint.y() - startPoint.y(), 2));
        painter.drawEllipse(startPoint, radius, radius);
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

#endif // CIRCLESHAPE_H
