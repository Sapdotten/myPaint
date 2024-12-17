#include "../include/palette.h"
#include <QPainter>
#include <QMouseEvent>

Palette::Palette(QWidget *parent)
    : QWidget(parent), rectSize(40) {
    // Задаём 20 фиксированных цветов
    colors = {
        Qt::black, Qt::white, Qt::red, Qt::green, Qt::blue,
        Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkRed,
        Qt::darkGreen, Qt::darkBlue, Qt::darkYellow, Qt::darkCyan,
        Qt::darkMagenta, Qt::lightGray, QColor("#FF5733"), QColor("#33FF57"),
        QColor("#3357FF"), QColor("#F1C40F")
    };

    // Устанавливаем фиксированный размер виджета
    int rows = (colors.size() + 4) / 5; // 5 прямоугольников в ряд
    setFixedSize(5 * rectSize, rows * rectSize);
}

void Palette::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Рисуем прямоугольники с цветами
    for (size_t i = 0; i < colors.size(); ++i) {
        int row = i / 5;
        int col = i % 5;

        QRect rect(col * rectSize, row * rectSize, rectSize, rectSize);
        painter.fillRect(rect, colors[i]);
        painter.setPen(Qt::black); // Рамка
        painter.drawRect(rect);
    }
}

void Palette::mousePressEvent(QMouseEvent *event) {
    int index = getColorIndexAt(event->pos());
    if (index >= 0 && index < static_cast<int>(colors.size())) {
        emit colorSelected(colors[index]); // Отправляем сигнал с выбранным цветом
    }
}

int Palette::getColorIndexAt(const QPoint &point) const {
    int col = point.x() / rectSize;
    int row = point.y() / rectSize;

    int index = row * 5 + col; // Рассчитываем индекс
    return (index < static_cast<int>(colors.size())) ? index : -1;
}
