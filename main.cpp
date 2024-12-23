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
#include <QListWidgetItem>
#include "include/canvas.h"
#include "include/palette.h"
#include "include/TrialChecker.h"


class BrushControl : public QWidget {
public:
    explicit BrushControl(Canvas *canvas, QWidget *parent = nullptr)
        : QWidget(parent), canvas(canvas) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *label = new QLabel("Толщина кисти:", this);
        layout->addWidget(label);

        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(1, 50);
        slider->setValue(canvas->getBrushThickness());
        layout->addWidget(slider);

        QLabel *thicknessLabel = new QLabel(QString::number(canvas->getBrushThickness()), this);
        layout->addWidget(thicknessLabel);

        connect(slider, &QSlider::valueChanged, this, [this, thicknessLabel, canvas](int value) {
            canvas->setBrushThickness(value);
            thicknessLabel->setText(QString::number(value));
        });
        QLabel *polygonSidesLabel = new QLabel("Стороны многоугольника: 3", this);
        QSlider *polygonSidesSlider = new QSlider(Qt::Horizontal, this);
        polygonSidesSlider->setRange(3, 12);
        polygonSidesSlider->setValue(3);

        layout->addWidget(polygonSidesLabel);
        layout->addWidget(polygonSidesSlider);


        connect(polygonSidesSlider, &QSlider::valueChanged, this, [this, polygonSidesLabel, canvas](int value) {
            polygonSidesLabel->setText(QString("Стороны многоугольника: %1").arg(value));
            canvas->setPolygonSides(value);
        });
    }

private:
    Canvas *canvas;
};

class InstrumentsControl : public QWidget {
public:
    explicit InstrumentsControl(Canvas *canvas, QWidget *parent = nullptr) : QWidget(parent), canvas(canvas) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QPushButton *brushButton = new QPushButton("Кисть", this);
        QPushButton *eraserButton = new QPushButton("Ластик", this);

        QPushButton *lineButton = new QPushButton("Прямая", this);
        QPushButton *rectButton = new QPushButton("Прямоугольник", this);
        QPushButton *circleButton = new QPushButton("Круг", this);
        QPushButton *triangleButton = new QPushButton("Треугольник", this);
        QPushButton *fillButton = new QPushButton("Заливка", this);
        QPushButton *polylineButton = new QPushButton("Ломаная", this);
        QPushButton *polygonButton = new QPushButton("Многоугольник", this);

        layout->addWidget(polygonButton);
        layout->addWidget(polylineButton);
        layout->addWidget(fillButton);
        layout->addWidget(brushButton);
        layout->addWidget(eraserButton);
        layout->addWidget(lineButton);
        layout->addWidget(rectButton);
        layout->addWidget(circleButton);
        layout->addWidget(triangleButton);

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


        connect(fillButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::FillTool);
        });
        connect(polylineButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::PolylineTool);
        });

        connect(polygonButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->setToolType(Brush::PolygonTool);
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

        connect(palette, &Palette::colorSelected, canvas, &Canvas::setBrushColor);
    }

private:
    Canvas *canvas;
};


class InstrumentsAndBrushControl : public QWidget {
public:
    explicit InstrumentsAndBrushControl(Canvas *canvas, QWidget *parent = nullptr)
        : QWidget(parent), canvas(canvas) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        BrushControl *brushControl = new BrushControl(canvas, this);
        layout->addWidget(brushControl);
        InstrumentsControl *instrumentsControl = new InstrumentsControl(canvas, this);
        PaletteControl *paletteControl = new PaletteControl(canvas, this);
        layout->addWidget(paletteControl);
        layout->addWidget(brushControl);
        layout->addWidget(instrumentsControl);

        QHBoxLayout *zoomLayout = new QHBoxLayout();
        QPushButton *zoomInButton = new QPushButton("Увеличить", this);
        QPushButton *zoomOutButton = new QPushButton("Уменьшить", this);
        zoomLayout->addWidget(zoomInButton);
        zoomLayout->addWidget(zoomOutButton);

        layout->addLayout(zoomLayout);
        QPushButton *saveButton = new QPushButton("Сохранить холст", this);
        layout->addWidget(saveButton);

        connect(saveButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->saveToFile();
        });
        connect(zoomInButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->zoomIn();
        });

        connect(zoomOutButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->zoomOut();
        });
        QPushButton *openFileButton = new QPushButton("Открыть файл", this);
        layout->addWidget(openFileButton);

        connect(openFileButton, &QPushButton::clicked, this, [this, canvas]() {
            QString fileName = QFileDialog::getOpenFileName(this, "Открыть изображение", "",
                                                            "Изображения (*.png *.jpeg *.jpg)");
            if (!fileName.isEmpty()) {
                canvas->openImageAsLayer(fileName);
            }
        });
    }

private:
    Canvas *canvas;
};


class LayerControl : public QWidget {
public:
    explicit LayerControl(Canvas *canvas, QWidget *parent = nullptr) : QWidget(parent), canvas(canvas) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        QPushButton *addLayerButton = new QPushButton("Добавить слой", this);
        layout->addWidget(addLayerButton);

        connect(addLayerButton, &QPushButton::clicked, this, [this, canvas]() {
            canvas->addLayer("Layer " + QString::number(layerList->count() + 1));
            updateLayerList();
        });

        layerList = new QListWidget(this);
        layout->addWidget(layerList);
        layerList->setDragDropMode(QAbstractItemView::InternalMove);

        connect(layerList, &QListWidget::currentRowChanged, this, [this, canvas](int index) {
            canvas->setActiveLayer(index);
        });

        connect(layerList, &QListWidget::clicked, this, [this, canvas]() {
            updateLayerList();
        });

        connect(layerList->model(), &QAbstractItemModel::rowsMoved, this, [this, canvas]() {
            updateCanvasLayerOrder();
        });

        QPushButton *toggleVisibilityButton = new QPushButton("Скрыть/Показать", this);
        layout->addWidget(toggleVisibilityButton);

        connect(toggleVisibilityButton, &QPushButton::clicked, this, [this, canvas]() {
            int index = canvas->getActiveLayerIndex();
            canvas->toggleLayerVisibility(index);

            updateLayerList();
        });
        QPushButton *deleteLayerButton = new QPushButton("Удалить слой", this);
        layout->addWidget(deleteLayerButton);

        connect(deleteLayerButton, &QPushButton::clicked, this, [this, canvas]() {
            int index = canvas->getActiveLayerIndex();
            canvas->removeLayer(index);
            updateLayerList();
        });

        updateLayerList();
        setLayout(layout);
    }

private:
    Canvas *canvas;
    QListWidget *layerList;

    void updateLayerList() {
        layerList->clear();
        int activeLayerId = canvas->getLayers()[canvas->getActiveLayerIndex()].getId();

        for (int i = 0; i < canvas->getLayers().size(); ++i) {
            const auto &layer = canvas->getLayers()[i];
            QString itemText = layer.isVisible() ? layer.getName() : layer.getName() + " (Скрыт)";
            auto *item = new QListWidgetItem(itemText, layerList);

            if (layer.getId() == activeLayerId) {
                item->setBackground(Qt::yellow);
            }
        }
    }

    void updateCanvasLayerOrder() {
        std::vector<Layer> newOrder;
        int activeLayerId = canvas->getLayers()[canvas->getActiveLayerIndex()].getId();

        for (int i = 0; i < layerList->count(); ++i) {
            QString layerName = layerList->item(i)->text();
            layerName = layerName.replace(" (Скрыт)", "");

            for (const auto &layer: canvas->getLayers()) {
                if (layer.getName() == layerName) {
                    newOrder.push_back(layer);
                    break;
                }
            }
        }

        canvas->setLayers(newOrder);

        for (int i = 0; i < newOrder.size(); ++i) {
            if (newOrder[i].getId() == activeLayerId) {
                canvas->setActiveLayer(i);
                break;
            }
        }
    }
};


class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        QSplitter *splitter = new QSplitter(Qt::Horizontal, centralWidget);
        Canvas *canvas = new Canvas(splitter);

        QWidget *leftPanel = new QWidget(splitter);
        QHBoxLayout *leftLayout = new QHBoxLayout(leftPanel);
        InstrumentsAndBrushControl *instrumentsAndBrushControl = new InstrumentsAndBrushControl(canvas, leftPanel);
        LayerControl *layerControl = new LayerControl(canvas, leftPanel);

        leftLayout->addWidget(layerControl);
        leftLayout->addWidget(instrumentsAndBrushControl);

        splitter->addWidget(leftPanel);
        splitter->addWidget(canvas);
        splitter->setSizes({200, 1000});

        setCentralWidget(splitter);
        setWindowTitle("Графический редактор");
        setFixedSize(1200, 1000);
    }
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TrialChecker checker;
    if (checker.isTrialValid()) {
        MainWindow mainWindow;
        mainWindow.show();

        return app.exec();
    } else {
        QMessageBox::critical(nullptr, "Триальный период",
                              "Триальный период истёк или обнаружена подделка. Приложение будет закрыто.");
        return 1;
    }
}
