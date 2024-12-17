#include <QPainter>
#include <QMouseEvent>
#include "../include/canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
      layer(new Layer(800, 600)),
      brush(5, Qt::black, Brush::BrushTool), // Изначально кисть
      drawing(false) {
    setFixedSize(800, 600);
}

void Canvas::setBrushColor(const QColor &color) {
    brush.setColor(color);
}

void Canvas::setBrushTool(Brush::ToolType toolType) {
    brush.setToolType(toolType);
}

void Canvas::setBrushThickness(int thickness) {
    brush.setThickness(thickness);
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, layer->getImage());
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
        drawLineTo(lastPoint);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawing && (event->buttons() & Qt::LeftButton)) {
        drawLineTo(event->pos());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = false; // Завершаем рисование
    }
}

void Canvas::drawLineTo(const QPoint &endPoint) {
    QPainter painter(&layer->getImage());

    // Устанавливаем цвет в зависимости от инструмента
    if (brush.getToolType() == Brush::EraserTool) {
        painter.setPen(QPen(Qt::white, brush.getThickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter.setPen(QPen(brush.getColor(), brush.getThickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    painter.drawLine(lastPoint, endPoint);
    lastPoint = endPoint;
    update();
}

void Canvas::setToolType(Brush::ToolType tool) {
    brush.setToolType(tool);
}
