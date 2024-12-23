//
// Created by Alexandra on 21.12.2024.
//

#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H
#include <QWidget>
#include <QVector>
#include <QImage>
#include <QPointF>
#include <QStack>
#include <QFileDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include "shape.h"

class PolygonShape : public Shape {
public:
    PolygonShape(const QColor &color, int thickness, int sides);

    void setStartPoint(const QPoint &point) override;

    void setEndPoint(const QPoint &point) override;

    void draw(QPainter &painter) const override;

private:
    QPoint center;
    double radius = 0;
    int sides;
    QColor color;
    int thickness;
};

#endif //POLYGONSHAPE_H
