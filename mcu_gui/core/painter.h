#ifndef PAINTER_H
#define PAINTER_H

#include "primitives.h"
#include "color32.h"

namespace McuGui {

class AbstractPainter {
public:
    AbstractPainter(): area_(DEFAULT_DISPLAY), pen_(COLOR_WHITE) {};
    explicit AbstractPainter(Dimension area): area_(area), pen_(COLOR_WHITE) {};
    void setPen(Color color) { pen_ = color; };

    // overloaded draw
    void draw(Point point) { drawPoint(point); }
    void draw(Line line) { drawLine(line); }
    void draw(Rectangle rectangle) { drawRectangle(rectangle); }
    void draw(Triangle triangle) { drawTriangle(triangle); }

    // functions to overide
    virtual void drawPoint(Point point);
    virtual void drawLine(Line line) = 0;
    virtual void drawTriangle(Triangle triangle) = 0;
    virtual void drawRectangle(Rectangle rectangle) = 0;
    void setLocalOrigin(Position pos) { origin_ = pos; };
    Position getLocalOrigin() const { return origin_; };

protected:
    virtual void plot(CoordType x, CoordType y, Color c) = 0;
    Position origin_;
    const Dimension area_;
    Color pen_;
};

class GeometricPainter: public AbstractPainter {
public:
    using AbstractPainter::AbstractPainter;
    virtual void drawLine(Line line) override;
    virtual void drawTriangle(Triangle triangle) override;
    virtual void drawRectangle(Rectangle rectangle) override;

protected:
    using AbstractPainter::plot;
};

class MemoryPainter: public GeometricPainter {
public:
    explicit MemoryPainter(Color* ptr): GeometricPainter(), ptr_(ptr) {};

protected:
    virtual void plot(CoordType x, CoordType y, Color c) override;
    Color* const ptr_;
};

// TODO: Inverted memory painter - to draw y from bottom

} // end namespace McuGui

#endif // PAINTER_H
