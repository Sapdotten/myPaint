#ifndef CANVAS_H
#define CANVAS_H
// canvas.h
#include <QWidget>
#include <QVector>
#include <QImage>
#include <QPointF>
#include <QStack>
#include <QFileDialog>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include "layer.h"
#include "brush.h"
#include "shape.h"
#include "rectangleshape.h"
#include "triangleshape.h"
#include "circleshape.h"
#include "lineshape.h"
#include "polygonshape.h"
#include "QMessageBox"
#include <QGraphicsDropShadowEffect>

class Canvas : public QWidget {
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

    void setBrushColor(const QColor &color);
    void setBrushThickness(int thickness);
    int getBrushThickness() const;
    void setToolType(Brush::ToolType tool);
    void addLayer(const QString &name);
    void toggleLayerVisibility(int index);
    const std::vector<Layer> &getLayers() const;
    void setActiveLayer(int index);
    int getActiveLayerIndex() const;
    void setLayers(const std::vector<Layer> &newLayers);
    void removeLayer(int index);
    void saveToFile();
    void zoomIn();
    void zoomOut();
    int getScaleFactor() const;
    void openImageAsLayer(const QString &filePath);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void setPolygonSides(int sides);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


private:
    int polygonSides = 3;
    QVector<QPoint> polylinePoints;
    bool isDrawingPolyline = false;
    void drawLineTo(const QPoint &endPoint);
    void fillArea(const QPoint &start, const QColor &fillColor);
    bool isPointInsideCanvas(const QPoint &point) const;
    QPointF mapToCanvasCoordinates(const QPoint &widgetPoint) const;
    void zoomAt(const QPoint &mousePosition, double factor);

    std::vector<Layer> layers;
    int activeLayerIndex = -1;
    Brush brush;
    bool drawing = false;
    QPoint lastPoint;
    std::unique_ptr<Shape> currentShape;


    bool spacePressed = false;
    bool isPanning = false;
    QPoint lastMousePosition;
    QPointF offset;
    double scaleFactor = 1.0;
};


#endif // CANVAS_H
