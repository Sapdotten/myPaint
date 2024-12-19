#include "../include/layer.h"

Layer::Layer(int width, int height, const QString &name,int id)
    : image(width, height, QImage::Format_ARGB32_Premultiplied),
      visible(true), name(name), id(id) {
    image.fill(Qt::transparent); // Прозрачный фон по умолчанию
}

void Layer::drawPixel(const QPoint &point, const QColor &color, int thickness) {
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(color);
    pen.setWidth(thickness);
    painter.setPen(pen);

    painter.drawPoint(point);
}

QImage &Layer::getImage() {
    return image;
}

bool Layer::isVisible() const {
    return visible;
}

void Layer::setVisible(bool visibility) {
    visible = visibility;
}

QString Layer::getName() const {
    return name;
}

void Layer::setName(const QString &newName) {
    name = newName;
}

bool Layer::isActive() const {
    return active;
}

void Layer::setActive(bool active) {
    active = active;
}

int Layer::getId() const { return id; }
