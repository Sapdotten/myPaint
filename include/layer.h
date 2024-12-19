#ifndef LAYER_H
#define LAYER_H
#include <QImage>
#include <QSize>
#include <QPoint>
#include <QString>
#include <QPainter>

class Layer {
public:
    Layer(int width, int height, const QString &name = "New Layer", int id=0);

    void drawPixel(const QPoint &point, const QColor &color, int thickness);
    QImage& getImage();

    // Новая функциональность
    bool isVisible() const;
    bool isActive() const;
    void setActive(bool active);
    void setVisible(bool visibility);
    QString getName() const;
    void setName(const QString &name);
    int getId() const;

private:
    QImage image;      // Изображение слоя
    bool visible;      // Видимость слоя
    QString name;      // Название слоя
    bool active;
    int id;
};

#endif // LAYER_H
