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
        void colorSelected(const QColor &color);

private:
    QSlider *redSlider;
    QSlider *greenSlider;
    QSlider *blueSlider;
    QSlider *alphaSlider;
    QLabel *colorPreview;
    QVector<QColor> savedColors;

    QColor currentColor;

    void setupUI();
    void setSliderColor(QSlider *slider, const QColor &color);

    private slots:
        void updateColor();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // PALETTE_H
