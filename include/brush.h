#ifndef BRUSH_H
#define BRUSH_H

#include <QColor>

class Brush {
public:
    enum ToolType {
        BrushTool,
        EraserTool,
        LineTool,
        RectangleTool,
        CircleTool,
        TriangleTool,
        FillTool,
        PolylineTool,
        PolygonTool
    };

    Brush(int thickness = 1, QColor color = Qt::black, ToolType toolType = BrushTool)
        : thickness(thickness), color(color), toolType(toolType) {
    }
    int getThickness() const;

    void setThickness(int newThickness);

    QColor getColor() const;

    void setColor(const QColor &newColor);

    ToolType getToolType() const;

    void setToolType(ToolType newToolType);

private:
    int thickness;
    QColor color;
    ToolType toolType;
};

#endif // BRUSH_H
