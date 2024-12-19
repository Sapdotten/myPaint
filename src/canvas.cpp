#include <QPainter>
#include <QMouseEvent>
#include "../include/canvas.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
      layer(new Layer(800, 600)),
      brush(5, Qt::black, Brush::BrushTool), // Изначально кисть
      drawing(false) {
    setFixedSize(800, 600);
}

void Canvas::setBrushColor(const QColor &color) {
    brush.setColor(color);
}

// void Canvas::setBrushTool(Brush::ToolType toolType) {
//     brush.setToolType(toolType);
// }

void Canvas::setBrushThickness(int thickness) {
    brush.setThickness(thickness);
}

int Canvas::getBrushThickness() const {
    return brush.getThickness();
}


void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        switch (brush.getToolType()) {
            case Brush::LineTool:
                currentShape = std::make_unique<LineShape>(brush.getColor(), brush.getThickness());
                break;
            case Brush::RectangleTool:
                currentShape = std::make_unique<RectangleShape>(brush.getColor(), brush.getThickness());
                break;
            case Brush::CircleTool:
                currentShape = std::make_unique<CircleShape>(brush.getColor(), brush.getThickness());
                break;
            case Brush::TriangleTool:
                currentShape = std::make_unique<TriangleShape>(brush.getColor(), brush.getThickness());
                break;
            default:
                lastPoint = event->pos();
                drawing = true;
                drawLineTo(lastPoint);
                return;
        }
        currentShape->setStartPoint(event->pos());
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (currentShape && (event->buttons() & Qt::LeftButton)) {
        currentShape->setEndPoint(event->pos());
        update();
    }
    else if (drawing && (event->buttons() & Qt::LeftButton)) {
        drawLineTo(event->pos());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && currentShape) {
        currentShape->setEndPoint(event->pos());

        if (activeLayerIndex >= 0 && activeLayerIndex < layers.size()) {
            QImage &image = layers[activeLayerIndex].getImage();
            QPainter painter(&image);
            currentShape->draw(painter); // Сохраняем фигуру на слой
        }

        currentShape.reset(); // Удаляем текущую фигуру
        update();
    }
    if (event->button() == Qt::LeftButton) {
        drawing = false;
    }
}


void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Рисуем все слои
    for (auto &layer: layers) {
        if (layer.isVisible()) {
            painter.drawImage(0, 0, layer.getImage());
        }
    }

    // Рисуем текущую фигуру
    if (currentShape) {
        currentShape->draw(painter);
    }
}

void Canvas::drawLineTo(const QPoint &endPoint) {
    // Проверка на существование активного слоя
    if (activeLayerIndex >= 0 && activeLayerIndex < layers.size()) {
        QImage &image = layers[activeLayerIndex].getImage();

        // Если инструмент выбран как ластик
        if (brush.getToolType() == Brush::EraserTool) {
            QPainter painter(&image);
            painter.setCompositionMode(QPainter::CompositionMode_Clear); // Используем режим очистки
            painter.setPen(QPen(Qt::transparent, brush.getThickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, endPoint);
            painter.end();
        } else {
            QPainter painter(&image);
            painter.setPen(QPen(brush.getColor(), brush.getThickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, endPoint);
        }

        lastPoint = endPoint;
        update();
    }
}


void Canvas::setToolType(Brush::ToolType tool) {
    brush.setToolType(tool);
}

void Canvas::addLayer(const QString &name) {
    static int layerIdCounter = 0;
    layers.emplace_back(width(), height(), name,layerIdCounter++); // Добавление слоя в список
    activeLayerIndex = layers.size() - 1; // Устанавливаем новый слой как активный
    update();
}


void Canvas::toggleLayerVisibility(int index) {
    if (index >= 0 && index < layers.size()) {
        layers[index].setVisible(!layers[index].isVisible());
        update();
    }
}


const std::vector<Layer> &Canvas::getLayers() const {
    return layers;
}

void Canvas::setActiveLayer(int index) {
    if (index >= 0 && index < layers.size()) {
        activeLayerIndex = index;
        update();
    } else {
        qWarning() << "Index out of bounds";
    }
}

int Canvas::getActiveLayerIndex() const {
    return activeLayerIndex;
}

void Canvas::setLayers(const std::vector<Layer> &newLayers) {
    layers = newLayers;
    update(); // Обновляем холст
}

void Canvas::setBrushTool(Brush::ToolType toolType) {
    brush.setToolType(toolType);
    update(); // Обновляем холст для применения нового инструмента
}

void Canvas::removeLayer(int index) {
    if (index >= 0 && index < layers.size()) {
        layers.erase(layers.begin() + index); // Удаляем слой
        if (activeLayerIndex >= layers.size()) {
            activeLayerIndex = layers.size() - 1; // Корректируем индекс активного слоя
        }
        update(); // Перерисовываем холст
    }
}

void Canvas::saveToFile() {
    // Создаём QImage с размерами холста
    QImage image(this->size(), QImage::Format_RGB32);
    QPainter painter(&image);

    // Рисуем содержимое холста на изображении
    render(&painter);
    painter.end();

    // Открытие диалогового окна для выбора пути и имени файла
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как", "", "Images (*.jpg *.jpeg)");

    if (!fileName.isEmpty()) {
        // Сохранение изображения в файл в формате JPEG
        image.save(fileName, "JPEG");
    }
}
