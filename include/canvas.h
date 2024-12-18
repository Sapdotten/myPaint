#ifndef CANVAS_H
#define CANVAS_H
#include <QWidget>
#include "layer.h"
#include "brush.h"
#include <vector>
#include "LineShape.h"
#include "RectangleShape.h"
#include "CircleShape.h"
#include "TriangleShape.h"

class Canvas : public QWidget {
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas() override = default;


    void setBrushColor(const QColor &color);
    void setBrushTool(Brush::ToolType toolType); // Устанавливает текущий инструмент
    void setBrushThickness(int thickness);
    void setToolType(Brush::ToolType tool);
    int getBrushThickness() const;

    // Управление слоями
    void addLayer(const QString &name);
    void setActiveLayer(int index);
    void toggleLayerVisibility(int index);

    const std::vector<Layer>& getLayers() const;
    int getActiveLayerIndex() const;
    void setLayers(const std::vector<Layer> &newLayers);
    // Устанавливает активный слой

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Layer *layer;
    Brush brush;
    QPoint lastPoint; // Хранит последнюю точку для соединения линий
    bool drawing;     // Флаг, указывающий, идет ли рисование

    void drawLineTo(const QPoint &endPoint);
    std::vector<Layer> layers; // Список слоев
    int activeLayerIndex;      // Индекс активного слоя
    std::unique_ptr<Shape> currentShape;


};
#endif // CANVAS_H
