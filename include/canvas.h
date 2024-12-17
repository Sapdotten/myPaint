#ifndef CANVAS_H
#define CANVAS_H
#include <QWidget>
#include "layer.h"
#include "brush.h"

class Canvas : public QWidget {
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas() override = default;

    void setBrushColor(const QColor &color); // Метод для изменения цвета кисти

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Layer *layer;
    Brush brush;
    QPoint lastPoint; // Хранит последнюю точку для соединения линий
    bool drawing;     // Флаг, указывающий, идет ли рисование

    void drawLineTo(const QPoint &endPoint);
};

#endif // CANVAS_H