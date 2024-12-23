#ifndef LINESHAPE_H
#define LINESHAPE_H

#include "Shape.h"

class LineShape : public Shape {
public:
    LineShape(const QColor &color, int thickness);

    void draw(QPainter &painter) const override;

    void setStartPoint(const QPoint &point) override;

    void setEndPoint(const QPoint &point) override;

private:
    QPoint startPoint, endPoint;
    QColor color;
    int thickness;
};

#endif // LINESHAPE_H
