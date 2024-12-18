#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include "Shape.h"

class RectangleShape : public Shape {
public:
    RectangleShape(const QColor &color, int thickness)
        : color(color), thickness(thickness) {}

    void draw(QPainter &painter) const override {
        painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(QRect(startPoint, endPoint));
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

#endif // RECTANGLESHAPE_H
