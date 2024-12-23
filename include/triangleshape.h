#ifndef TRIANGLESHAPE_H
#define TRIANGLESHAPE_H

#include "Shape.h"

class TriangleShape : public Shape {
public:
    TriangleShape(const QColor &color, int thickness);

    void draw(QPainter &painter) const override;

    void setStartPoint(const QPoint &point) override;

    void setEndPoint(const QPoint &point) override;

private:
    QPoint startPoint, endPoint;
    QColor color;
    int thickness;
};

#endif // TRIANGLESHAPE_H
