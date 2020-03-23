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
    virtual void draw(Point point);
    virtual void draw(Line line) = 0;
    virtual void draw(Rectangle rectangle) = 0;
    virtual void draw(Triangle triangle) = 0;
    virtual void draw(const Mask& mask);

    // functions to overide
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
    virtual void draw(Point point) override { AbstractPainter::draw(point); };
    virtual void draw(const Mask& mask) override { AbstractPainter::draw(mask); };
    virtual void draw(Line line) override;
    virtual void draw(Triangle triangle) override;
    virtual void draw(Rectangle rectangle) override;

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
