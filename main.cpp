#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QListWidget>
#include "include/canvas.h"
#include "include/palette.h"


class BrushControl : public QWidget {
public:
    explicit BrushControl(Canvas *canvas, QWidget *parent = nullptr)
        : QWidget(parent), canvas(canvas) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Заголовок для настройки толщины
        QLabel *label = new QLabel("Толщина кисти:", this);
        layout->addWidget(label);

        // Ползунок для изменения толщины
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(1, 50); // Минимальная и максимальная толщина кисти
        slider->setValue(canvas->getBrushThickness()); // Текущее значение толщины
        layout->addWidget(slider);

        // Отображение текущего значения толщины
        QLabel *thicknessLabel = new QLabel(QString::number(canvas->getBrushThickness()), this);
        layout->addWidget(thicknessLabel);

        // Подключаем сигнал от ползунка к изменению толщины кисти
        connect(slider, &QSlider::valueChanged, this, [this, thicknessLabel, canvas](int value) {
            canvas->setBrushThickness(value); // Устанавливаем новую толщину
            thicknessLabel->setText(QString::number(value)); // Обновляем отображение толщины
        });
    }

private:
    Canvas *canvas;
};

class InstrumentsControl : public QWidget {
public:
    explicit InstrumentsControl(Canvas *canvas, QWidget *parent = nullptr) : QWidget(parent), canvas(canvas) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Кнопки для инструментов
        QPushButton *brushButton = new QPushButton("Кисть", this);
        QPushButton *eraserButton = new QPushButton("Ластик", this);

        // Кнопки для фигур
        QPushButton *lineButton = new QPushButton("Прямая", this);
        QPushButton *rectButton = new QPushButton("Прямоугольник", this);
        QPushButton *circleButton = new QPushButton("Круг", this);
        QPushButton *triangleButton = new QPushButton("Треугольник", this);

        // Добавляем кнопки в макет
        layout->addWidget(brushButton);
        layout->addWidget(eraserButton);
        layout->addWidget(lineButton);
        layout->addWidget(rectButton);
        layout->addWidget(circleButton);
        layout->addWidget(triangleButton);

        // Подключаем сигналы к слотам
        connect(brushButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::BrushTool);
        });

        connect(eraserButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::EraserTool);
        });

        connect(lineButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::LineTool);
        });

        connect(rectButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::RectangleTool);
        });

        connect(circleButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::CircleTool);
        });

        connect(triangleButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::TriangleTool);
        });
    }

private:
    Canvas *canvas;
};




class PaletteControl : public QWidget {
public:
    explicit PaletteControl(Canvas *canvas, QWidget *parent = nullptr) : QWidget(parent), canvas(canvas) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        Palette *palette = new Palette(this);
        layout->addWidget(palette);

        // Подключаем сигнал палитры к изменению цвета кисти
        connect(palette, &Palette::colorSelected, canvas, &Canvas::setBrushColor);

        QPushButton *button = new QPushButton("Palette", this);
        layout->addWidget(button);
    }

private:
    Canvas *canvas; // Указатель на объект Canvas
};


class InstrumentsAndBrushControl : public QWidget {
public:
    InstrumentsAndBrushControl(Canvas *canvas, QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        BrushControl *brushControl = new BrushControl(canvas, this);
        layout->addWidget(brushControl);
        InstrumentsControl *instrumentsControl = new InstrumentsControl(canvas, this);
        PaletteControl *paletteControl = new PaletteControl(canvas, this);

        layout->addWidget(paletteControl);
        layout->addWidget(brushControl);
        layout->addWidget(instrumentsControl);
    }
};

class LayerControl : public QWidget {
public:
    explicit LayerControl(Canvas *canvas, QWidget *parent = nullptr) : QWidget(parent), canvas(canvas) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Кнопка добавления слоя
        QPushButton *addLayerButton = new QPushButton("Добавить слой", this);
        layout->addWidget(addLayerButton);

        connect(addLayerButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->addLayer("Layer " + QString::number(layerList->count() + 1));
            updateLayerList();
        });

        // Список слоев
        layerList = new QListWidget(this);
        layout->addWidget(layerList);
        layerList->setDragDropMode(QAbstractItemView::InternalMove);

        connect(layerList, &QListWidget::currentRowChanged, this, [this, canvas](int index) {
            canvas->setActiveLayer(index);
        });

        connect(layerList->model(), &QAbstractItemModel::rowsMoved, this, [this]() {
        updateCanvasLayerOrder();
    });

        // Кнопка скрытия/показа слоя
        QPushButton *toggleVisibilityButton = new QPushButton("Скрыть/Показать", this);
        layout->addWidget(toggleVisibilityButton);

        connect(toggleVisibilityButton, &QPushButton::clicked, this, [this, canvas]() {
            int index = canvas->getActiveLayerIndex();
            canvas->toggleLayerVisibility(index);
            updateLayerList();
        });

        setLayout(layout);
    }

private:
    Canvas *canvas;
    QListWidget *layerList;

    void updateLayerList() {
        layerList->clear();
        for (const auto &layer: canvas->getLayers()) {
            layerList->addItem(layer.isVisible() ? layer.getName() : layer.getName() + " (Скрыт)");
        }
    }
    void updateCanvasLayerOrder() {
        std::vector<Layer> newOrder;

        for (int i = 0; i < layerList->count(); ++i) {
            QString layerName = layerList->item(i)->text();
            layerName = layerName.replace(" (Скрыт)", ""); // Убираем метку скрытого слоя

            // Ищем слой с таким именем в текущем порядке
            for (const auto &layer : canvas->getLayers()) {
                if (layer.getName() == layerName) {
                    newOrder.push_back(layer);
                    break;
                }
            }
        }

        canvas->setLayers(newOrder);
    }
};


class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Создаем главный виджет окна
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Создаем разделитель
        QSplitter *splitter = new QSplitter(Qt::Horizontal, centralWidget);

        // Создаем холст
        Canvas *canvas = new Canvas(splitter);

        // Создаем панели для управления кистью и слоями
        QWidget *leftPanel = new QWidget(splitter);
        QHBoxLayout *leftLayout = new QHBoxLayout(leftPanel);

        InstrumentsAndBrushControl *instrumentsAndBrushControl = new InstrumentsAndBrushControl(canvas, leftPanel);
        LayerControl *layerControl = new LayerControl(canvas, leftPanel);

        leftLayout->addWidget(layerControl);
        leftLayout->addWidget(instrumentsAndBrushControl);

        // Добавляем все в разделитель
        splitter->addWidget(leftPanel);
        splitter->addWidget(canvas);

        // Настроим разделитель, чтобы левая панель занимала определенное место
        splitter->setSizes({200, 600}); // 200 пикселей для панели и 600 для холста

        // Устанавливаем центральный виджет в окно
        setCentralWidget(splitter);

        setWindowTitle("Минимальный графический редактор");
        setFixedSize(800, 600);
    }
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
