#include <QPainter>
#include <QMouseEvent>
#include "../include/canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
      layer(new Layer(800, 600)),
      brush(5, Qt::black),
      drawing(false) { // Инициализация флага рисования
    setFixedSize(800, 600);
}

void Canvas::setBrushColor(const QColor &color) {
    brush.setColor(color); // Устанавливаем новый цвет кисти
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, layer->getImage());
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos(); // Устанавливаем начальную точку
        drawing = true;           // Начинаем рисование
        drawLineTo(lastPoint);    // Рисуем точку
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (drawing && (event->buttons() & Qt::LeftButton)) {
        drawLineTo(event->pos()); // Рисуем линию к новой точке
    }
}

void Canvas::drawLineTo(const QPoint &endPoint) {
    QPainter painter(&layer->getImage()); // Работаем с изображением слоя
    painter.setPen(QPen(brush.getColor(), brush.getThickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint); // Рисуем линию от последней точки к новой

    lastPoint = endPoint; // Обновляем последнюю точку
    update();             // Перерисовываем виджет
}
