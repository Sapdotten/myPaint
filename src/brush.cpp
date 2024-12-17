#include "../include/brush.h"

Brush::Brush(int thickness, QColor color, ToolType tool)
    : thickness(thickness), color(color), toolType(tool) {}

void Brush::setThickness(int thickness) { this->thickness = thickness; }
void Brush::setColor(const QColor &color) { this->color = color; }
void Brush::setToolType(ToolType tool) { this->toolType = tool; }

int Brush::getThickness() const { return thickness; }
QColor Brush::getColor() const { return color; }
Brush::ToolType Brush::getToolType() const { return toolType; }
