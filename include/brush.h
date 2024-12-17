//
// Created by Alexandra on 03.12.2024.
//

#ifndef BRUSH_H
#define BRUSH_H
#include <QColor>

class Brush {
public:
    Brush(int thickness = 5, QColor color = Qt::black);

    void setThickness(int thickness);
    void setColor(const QColor &color);

    int getThickness() const;
    QColor getColor() const;

private:
    int thickness;
    QColor color;
};
#endif //BRUSH_H
