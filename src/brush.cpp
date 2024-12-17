//
// Created by Alexandra on 03.12.2024.
//
#include "../include/brush.h"

Brush::Brush(int thickness, QColor color)
    : thickness(thickness), color(color) {}

void Brush::setThickness(int thickness) {
    this->thickness = thickness;
}

void Brush::setColor(const QColor &color) {
    this->color = color;
}

int Brush::getThickness() const {
    return thickness;
}

QColor Brush::getColor() const {
    return color;
}