//
// Created by Alexandra on 03.12.2024.
//

#ifndef LAYER_H
#define LAYER_H
#include <QImage>
#include <QSize>
#include <QPoint>

class Layer {
public:
    Layer(int width, int height);
    void drawPixel(const QPoint &point, const QColor &color, int thickness);

    QImage& getImage();

private:
    QImage image;
};
#endif //LAYER_H
