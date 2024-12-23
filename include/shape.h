#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPoint>

class Shape {
public:
    virtual ~Shape() = default;

    virtual void draw(QPainter &painter) const = 0;
    virtual void setStartPoint(const QPoint &point) = 0;
    virtual void setEndPoint(const QPoint &point) = 0;
};

#endif // SHAPE_H
