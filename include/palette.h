#ifndef PALETTE_H
#define PALETTE_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QColor>
#include <QGridLayout>
#include <QVector>

class Palette : public QWidget {
    Q_OBJECT

public:
    explicit Palette(QWidget *parent = nullptr);
    ~Palette() override = default;

    signals:
        void colorSelected(const QColor &color); // Сигнал для передачи выбранного цвета

private:
    QSlider *redSlider;
    QSlider *greenSlider;
    QSlider *blueSlider;
    QSlider *alphaSlider;
    QLabel *colorPreview;
    QVector<QColor> savedColors; // Сохраненные цвета

    QColor currentColor; // Объявление текущего цвета

    void setupUI(); // Устанавливает интерфейс
    void setSliderColor(QSlider *slider, const QColor &color); // Устанавливает стиль ползунков

    private slots:
        void updateColor(); // Обновляет текущий цвет

protected:
    bool eventFilter(QObject *watched, QEvent *event) override; // Обрабатывает клики на ячейки
    void paintEvent(QPaintEvent *event) override; // Для возможной доработки отрисовки
};

#endif // PALETTE_H
