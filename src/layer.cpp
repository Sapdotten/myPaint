//
// Created by Alexandra on 03.12.2024.
//
#include "../include/layer.h"
#include <QPainter>

Layer::Layer(int width, int height)
    : image(width, height, QImage::Format_ARGB32) {
    image.fill(Qt::white);
}

void Layer::drawPixel(const QPoint &point, const QColor &color, int thickness) {
    QPainter painter(&image);
    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawPoint(point);
}

QImage &Layer::getImage(){
    return image;
}