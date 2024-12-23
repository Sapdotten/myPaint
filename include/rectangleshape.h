#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include "shape.h"

class RectangleShape : public Shape {
public:
    RectangleShape(const QColor &color, int thickness);

    void draw(QPainter &painter) const override;

    void setStartPoint(const QPoint &point) override;

    void setEndPoint(const QPoint &point) override;

private:
    QPoint startPoint, endPoint;
    QColor color;
    int thickness;
};

#endif // RECTANGLESHAPE_H
