#include "../include/palette.h"
#include <QPainter>
#include <QMouseEvent>

Palette::Palette(QWidget *parent) : QWidget(parent), currentColor(Qt::black) {
    setupUI();
    updateColor();
}

void Palette::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Создаем слайдеры
    redSlider = new QSlider(Qt::Horizontal, this);
    greenSlider = new QSlider(Qt::Horizontal, this);
    blueSlider = new QSlider(Qt::Horizontal, this);
    alphaSlider = new QSlider(Qt::Horizontal, this);

    redSlider->setRange(0, 255);
    greenSlider->setRange(0, 255);
    blueSlider->setRange(0, 255);
    alphaSlider->setRange(0, 255);

    QLabel *redLabel = new QLabel("Красный:", this);
    QLabel *greenLabel = new QLabel("Зеленый:", this);
    QLabel *blueLabel = new QLabel("Синий:", this);
    QLabel *alphaLabel = new QLabel("Прозрачность:", this);

    colorPreview = new QLabel(this);
    colorPreview->setFixedSize(100, 50);
    colorPreview->setFrameShape(QFrame::Box);

    QGridLayout *colorGrid = new QGridLayout();
    for (int i = 0; i < 16; ++i) {
        QLabel *colorCell = new QLabel(this);
        colorCell->setFixedSize(30, 30);
        colorCell->setFrameShape(QFrame::Box);
        colorCell->setStyleSheet("background-color: rgba(0, 0, 0, 0);"); // Прозрачный фон
        colorCell->setProperty("index", i);


        colorCell->installEventFilter(this);

        savedColors.append(Qt::transparent);
        colorGrid->addWidget(colorCell, i / 4, i % 4);
    }

    mainLayout->addWidget(redLabel);
    mainLayout->addWidget(redSlider);
    mainLayout->addWidget(greenLabel);
    mainLayout->addWidget(greenSlider);
    mainLayout->addWidget(blueLabel);
    mainLayout->addWidget(blueSlider);
    mainLayout->addWidget(alphaLabel);
    mainLayout->addWidget(alphaSlider);
    mainLayout->addWidget(colorPreview);
    mainLayout->addLayout(colorGrid);

    setLayout(mainLayout);

    setSliderColor(redSlider, Qt::red);
    setSliderColor(greenSlider, Qt::green);
    setSliderColor(blueSlider, Qt::blue);
    setSliderColor(alphaSlider, Qt::gray);

    connect(redSlider, &QSlider::valueChanged, this, &Palette::updateColor);
    connect(greenSlider, &QSlider::valueChanged, this, &Palette::updateColor);
    connect(blueSlider, &QSlider::valueChanged, this, &Palette::updateColor);
    connect(alphaSlider, &QSlider::valueChanged, this, &Palette::updateColor);
}

void Palette::setSliderColor(QSlider *slider, const QColor &color) {
    QString sliderStyle = QString(
                "QSlider::groove:horizontal {"
                "    border: 1px solid #999999;"
                "    height: 8px;"
                "    background: %1;"
                "    margin: 2px 0;"
                "}"
                "QSlider::handle:horizontal {"
                "    background: #ffffff;"
                "    border: 1px solid #5c5c5c;"
                "    width: 18px;"
                "    margin: -2px 0;"
                "    border-radius: 3px;"
                "}")
            .arg(color.name());

    slider->setStyleSheet(sliderStyle);
}

void Palette::updateColor() {
    currentColor.setRed(redSlider->value());
    currentColor.setGreen(greenSlider->value());
    currentColor.setBlue(blueSlider->value());
    currentColor.setAlpha(alphaSlider->value());

    QPalette palette = colorPreview->palette();
    palette.setColor(QPalette::Window, currentColor);
    colorPreview->setAutoFillBackground(true);
    colorPreview->setPalette(palette);

    emit colorSelected(currentColor);
}

bool Palette::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QLabel *colorCell = qobject_cast<QLabel *>(watched);
        if (colorCell) {
            int index = colorCell->property("index").toInt();
            if (mouseEvent->button() == Qt::LeftButton) {
                QColor cellColor = savedColors[index];
                redSlider->setValue(cellColor.red());
                greenSlider->setValue(cellColor.green());
                blueSlider->setValue(cellColor.blue());
                alphaSlider->setValue(cellColor.alpha());
            } else if (mouseEvent->button() == Qt::RightButton) {
                savedColors[index] = currentColor;
                colorCell->setStyleSheet(QString("background-color: %1;").arg(currentColor.name(QColor::HexArgb)));
            }
        }
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void Palette::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
}
