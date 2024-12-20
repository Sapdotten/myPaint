#ifndef BRUSH_H
#define BRUSH_H

#include <QColor>

class Brush {
public:
    enum ToolType {
        BrushTool,      // Обычная кисть
        EraserTool,     // Ластик
        LineTool,       // Линия
        RectangleTool,  // Прямоугольник
        CircleTool,     // Круг
        TriangleTool,    // Треугольник
        FillTool, // Заливка
    PolylineTool
    };

    Brush(int thickness = 1, QColor color = Qt::black, ToolType toolType = BrushTool)
        : thickness(thickness), color(color), toolType(toolType) {}

    int getThickness() const;

    void setThickness(int newThickness);

    QColor getColor() const;

    void setColor(const QColor &newColor);

    ToolType getToolType() const;

    void setToolType(ToolType newToolType);


private:
    int thickness;       // Толщина кисти или границы фигуры
    QColor color;        // Цвет кисти или границы фигуры
    ToolType toolType;   // Текущий инструмент
};

#endif // BRUSH_H
