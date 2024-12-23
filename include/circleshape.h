#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

#include "Shape.h"

class CircleShape : public Shape {
public:
    CircleShape(const QColor &color, int thickness);
    void draw(QPainter &painter) const override;
    void setStartPoint(const QPoint &point) override;
    void setEndPoint(const QPoint &point) override;

private:
    QPoint startPoint, endPoint;
    QColor color;
    int thickness;
};

#endif // CIRCLESHAPE_H
