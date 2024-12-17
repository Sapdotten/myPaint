#ifndef BRUSH_H
#define BRUSH_H
#include <QColor>

class Brush {
public:
    enum ToolType { BrushTool, EraserTool }; // Инструменты: кисть и ластик

    Brush(int thickness = 5, QColor color = Qt::black, ToolType tool = BrushTool);

    void setThickness(int thickness);
    void setColor(const QColor &color);
    void setToolType(ToolType tool);

    int getThickness() const;
    QColor getColor() const;
    ToolType getToolType() const;

private:
    int thickness;
    QColor color;
    ToolType toolType;
};
#endif // BRUSH_H
