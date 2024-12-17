#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "include/canvas.h"
#include "include/palette.h"


class BrushControl : public QWidget {
public:
    BrushControl(QWidget *parent = nullptr) : QWidget(parent) {
        // Здесь можно разместить элементы управления кистью
        QVBoxLayout *layout = new QVBoxLayout(this);
        QPushButton *button = new QPushButton("Настроить кисть", this);
        layout->addWidget(button);
    }
};

class InstrumentsControl : public QWidget {
    // вообще здесь потом будет список иснтрументов и, наверное, эта хрень будет делать setTool
public:
    InstrumentsControl(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        QPushButton *button = new QPushButton("Выбрать инструмент", this);
        layout->addWidget(button);
    }
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
        BrushControl *brushControl = new BrushControl(this);
        InstrumentsControl *instrumentsControl = new InstrumentsControl(this);
        PaletteControl *paletteControl = new PaletteControl(canvas, this);
        layout->addWidget(paletteControl);
        layout->addWidget(brushControl);
        layout->addWidget(instrumentsControl);

    }
};

class LayerControl : public QWidget {
public:
    LayerControl(QWidget *parent = nullptr) : QWidget(parent) {
        // Здесь можно разместить элементы управления слоями
        QVBoxLayout *layout = new QVBoxLayout(this);
        QPushButton *button = new QPushButton("Управление слоями", this);
        layout->addWidget(button);
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
        LayerControl *layerControl = new LayerControl(leftPanel);

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
