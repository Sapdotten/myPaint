#ifndef PALETTE_H
#define PALETTE_H

#include <QWidget>
#include <QColor>
#include <vector>

class Palette : public QWidget {
    Q_OBJECT

public:
    explicit Palette(QWidget *parent = nullptr);
    ~Palette() override = default;

    signals:
        void colorSelected(const QColor &color); // Сигнал для передачи выбранного цвета

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    const int MAX_COLOR_VALUE = 255;
    std::vector<QColor> colors; // Список цветов
    int rectSize;              // Размер одного прямоугольника

    int getColorIndexAt(const QPoint &point) const; // Возвращает индекс цвета по координатам
    int getRedValue(const float theta) const;
    int getGreenValue(const float theta) const;
    int getBlueValue(const float theta) const;
    void drawColorCircle();
};

#endif // PALETTE_H
