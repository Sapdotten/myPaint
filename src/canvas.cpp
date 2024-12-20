// canvas.cpp
#include "../include/canvas.h"
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QStack>
#include <QWheelEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
      brush(5, Qt::black, Brush::BrushTool),
      drawing(false) {
    setFixedSize(800, 800);
    setFocusPolicy(Qt::StrongFocus); // Важно для обработки пробела
    addLayer("Default");
}

void Canvas::setBrushColor(const QColor &color) {
    brush.setColor(color);
}

void Canvas::setBrushThickness(int thickness) {
    brush.setThickness(thickness);
}

int Canvas::getBrushThickness() const {
    return brush.getThickness();
}

void Canvas::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        spacePressed = true;
    }
    QWidget::keyPressEvent(event);
}

void Canvas::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        spacePressed = false;
        // Если отпустили пробел во время панорамирования — завершаем панорамирование
        if (isPanning) {
            isPanning = false;
        }
    }
    QWidget::keyReleaseEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if ((event->button() == Qt::MiddleButton) || (event->button() == Qt::LeftButton && spacePressed)) {
        isPanning = true;
        lastMousePosition = event->pos();
        return;
    }

    if (event->button() == Qt::LeftButton) {
        QPointF canvasPoint = mapToCanvasCoordinates(event->pos());
        switch (brush.getToolType()) {
            case Brush::LineTool:
                currentShape = std::make_unique<LineShape>(brush.getColor(), brush.getThickness());
                currentShape->setStartPoint(canvasPoint.toPoint());
                break;
            case Brush::RectangleTool:
                currentShape = std::make_unique<RectangleShape>(brush.getColor(), brush.getThickness());
                currentShape->setStartPoint(canvasPoint.toPoint());
                break;
            case Brush::CircleTool:
                currentShape = std::make_unique<CircleShape>(brush.getColor(), brush.getThickness());
                currentShape->setStartPoint(canvasPoint.toPoint());
                break;
            case Brush::TriangleTool:
                currentShape = std::make_unique<TriangleShape>(brush.getColor(), brush.getThickness());
                currentShape->setStartPoint(canvasPoint.toPoint());
                break;
            case Brush::FillTool:
                fillArea(canvasPoint.toPoint(), brush.getColor());
                break;
            default:
                lastPoint = canvasPoint.toPoint();
                drawing = true;
                drawLineTo(lastPoint);
                return;
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (isPanning) {
        QPointF delta = event->pos() - lastMousePosition;
        offset += delta;
        lastMousePosition = event->pos();
        update();
        return;
    }

    if (currentShape && (event->buttons() & Qt::LeftButton)) {
        QPointF canvasPoint = mapToCanvasCoordinates(event->pos());
        currentShape->setEndPoint(canvasPoint.toPoint());
        update();
    } else if (drawing && (event->buttons() & Qt::LeftButton)) {
        QPointF canvasPoint = mapToCanvasCoordinates(event->pos());
        drawLineTo(canvasPoint.toPoint());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (isPanning && (event->button() == Qt::MiddleButton || event->button() == Qt::LeftButton)) {
        isPanning = false;
        return;
    }

    if (event->button() == Qt::LeftButton && currentShape) {
        QPointF canvasPoint = mapToCanvasCoordinates(event->pos());
        currentShape->setEndPoint(canvasPoint.toPoint());

        if (activeLayerIndex >= 0 && activeLayerIndex < (int)layers.size()) {
            QImage &image = layers[activeLayerIndex].getImage();
            QPainter painter(&image);
            currentShape->draw(painter);
        }

        currentShape.reset();
        update();
    }
    if (event->button() == Qt::LeftButton) {
        drawing = false;
    }
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.translate(offset);
    painter.scale(scaleFactor, scaleFactor);

    for (auto &layer : layers) {
        if (layer.isVisible()) {
            painter.drawImage(0, 0, layer.getImage());
        }
    }

    if (currentShape) {
        currentShape->draw(painter);
    }
}

void Canvas::drawLineTo(const QPoint &endPoint) {
    if (activeLayerIndex >= 0 && activeLayerIndex < (int)layers.size()) {
        QImage &image = layers[activeLayerIndex].getImage();
        QPainter painter(&image);

        if (brush.getToolType() == Brush::EraserTool) {
            painter.setCompositionMode(QPainter::CompositionMode_Clear);
            painter.setPen(QPen(Qt::transparent, brush.getThickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(lastPoint, endPoint);
        } else {
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
    layers.emplace_back(width(), height(), name, layerIdCounter++);
    activeLayerIndex = (int)layers.size() - 1;
    update();
}

void Canvas::toggleLayerVisibility(int index) {
    if (index >= 0 && index < (int)layers.size()) {
        layers[index].setVisible(!layers[index].isVisible());
        update();
    }
}

const std::vector<Layer> &Canvas::getLayers() const {
    return layers;
}

void Canvas::setActiveLayer(int index) {
    if (index >= 0 && index < (int)layers.size()) {
        activeLayerIndex = index;
        update();
    }
}

int Canvas::getActiveLayerIndex() const {
    return activeLayerIndex;
}

void Canvas::setLayers(const std::vector<Layer> &newLayers) {
    layers = newLayers;
    update();
}

void Canvas::removeLayer(int index) {
    if (index >= 0 && index < (int)layers.size()) {
        layers.erase(layers.begin() + index);
        if (activeLayerIndex >= (int)layers.size()) {
            activeLayerIndex = (int)layers.size() - 1;
        }
        update();
    }
}

void Canvas::saveToFile() {
    QImage image(this->size(), QImage::Format_RGB32);
    QPainter painter(&image);
    render(&painter);
    painter.end();
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как", "", "Images (*.jpg *.jpeg)");
    if (!fileName.isEmpty()) {
        image.save(fileName, "JPEG");
    }
}

void Canvas::fillArea(const QPoint &start, const QColor &fillColor) {
    if (!isPointInsideCanvas(start) || activeLayerIndex < 0 || activeLayerIndex >= (int)layers.size()) return;

    QImage &layerImage = layers[activeLayerIndex].getImage();
    QColor targetColor = layerImage.pixelColor(start);

    if (targetColor == fillColor) return;

    QStack<QPoint> stack;
    stack.push(start);

    while (!stack.isEmpty()) {
        QPoint point = stack.pop();
        if (!isPointInsideCanvas(point)) continue;
        if (layerImage.pixelColor(point) != targetColor) continue;

        layerImage.setPixelColor(point, fillColor);

        stack.push(QPoint(point.x() + 1, point.y()));
        stack.push(QPoint(point.x() - 1, point.y()));
        stack.push(QPoint(point.x(), point.y() + 1));
        stack.push(QPoint(point.x(), point.y() - 1));
    }
}

bool Canvas::isPointInsideCanvas(const QPoint &point) const {
    return point.x() >= 0 && point.x() < width() && point.y() >= 0 && point.y() < height();
}

void Canvas::zoomIn() {
    zoomAt(mapFromGlobal(QCursor::pos()), 1.05);
}

void Canvas::zoomOut() {
    zoomAt(mapFromGlobal(QCursor::pos()), 0.95);
}

void Canvas::wheelEvent(QWheelEvent *event) {
    double factor = (event->angleDelta().y() > 0) ? 1.05 : 0.95;
    zoomAt(event->position().toPoint(), factor);
}

int Canvas::getScaleFactor() const {
    return scaleFactor;
}

QPointF Canvas::mapToCanvasCoordinates(const QPoint &widgetPoint) const {
    return (widgetPoint - offset) / scaleFactor;
}

void Canvas::zoomAt(const QPoint &mousePosition, double factor) {
    QPointF mouseOnCanvas = (mousePosition - offset) / scaleFactor;

    scaleFactor *= factor;
    if (scaleFactor < 0.1) scaleFactor = 0.1;
    if (scaleFactor > 10.0) scaleFactor = 10.0;

    offset = mousePosition - mouseOnCanvas * scaleFactor;
    update();
}

void Canvas::openImageAsLayer(const QString &filePath) {
    QImage image;
    if (!image.load(filePath)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение.");
        return;
    }

    // Добавляем изображение как новый слой
    QString layerName = QFileInfo(filePath).fileName(); // Имя слоя совпадает с именем файла
    layers.emplace_back(image.width(), image.height(), layerName);
    layers.back().getImage() = image; // Загружаем изображение в слой

    activeLayerIndex = layers.size() - 1; // Новый слой становится активным
    update(); // Обновляем холст
}

