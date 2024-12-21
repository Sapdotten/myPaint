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
class PolygonShape : public Shape {
public:
    PolygonShape(const QColor &color, int thickness, int sides)
        : color(color), thickness(thickness), sides(sides) {}

    void setStartPoint(const QPoint &point) override {
        center = point;
    }

    void setEndPoint(const QPoint &point) override {
        radius = QLineF(center, point).length();
    }

    void draw(QPainter &painter) const override {
        if (sides < 3 || radius <= 0) return;

        QPolygon polygon;
        for (int i = 0; i < sides; ++i) {
            double angle = 2.0 * M_PI * i / sides;
            QPointF vertex(center.x() + radius * cos(angle), center.y() - radius * sin(angle));
            polygon << vertex.toPoint();
        }

        painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawPolygon(polygon);
    }

private:
    QPoint center;
    double radius = 0;
    int sides;
    QColor color;
    int thickness;
};

#endif //POLYGONSHAPE_H
