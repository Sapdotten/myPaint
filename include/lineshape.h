#ifndef LINESHAPE_H
#define LINESHAPE_H

#include "Shape.h"

class LineShape : public Shape {
public:
    LineShape(const QColor &color, int thickness)
        : color(color), thickness(thickness) {}

    void draw(QPainter &painter) const override {
        painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(startPoint, endPoint);
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

#endif // LINESHAPE_H
