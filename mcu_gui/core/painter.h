#ifndef PAINTER_H
#define PAINTER_H

#include "linear/matrix.h"
#include "paint_engine.h"

namespace McuGui {

class PainterInterface {
public:
    // coloring
    virtual void setPen(Color color) = 0;

    // drawing
    virtual void drawPoint(Position pos) const = 0;
    virtual void drawLine(Position start, Position end) const = 0;
    virtual void drawTriangle(Position v1, Position v2, Position v3) const = 0;
    virtual void drawMask(const Mask& mask) const = 0;
};

class SimplePainter: public PainterInterface {
public:
    SimplePainter(PaintEngineInterface& engine): engine_(engine) {};

    virtual void setPen(Color color) override { pen_ = color; };

    virtual void drawPoint(Position pos) const override;
    virtual void drawLine(Position start, Position end) const override;
    virtual void drawTriangle(Position v1, Position v2, Position v3) const override;
    virtual void drawMask(const Mask& mask) const override;

protected:
    const PaintEngineInterface& engine_;
    Color pen_ = COLOR_WHITE;
};

class MovedPainter: public PainterInterface {
public:
    MovedPainter(PainterInterface& base, CoordType dx, CoordType dy)
        : base_(base), dx_(dx), dy_(dy) {}

    // coloring
    virtual void setPen(Color color) override { base_.setPen(color); };

    // drawing
    virtual void drawPoint(Position pos) const override;
    virtual void drawLine(Position start, Position end) const override;
    virtual void drawTriangle(Position v1, Position v2, Position v3) const override;
    virtual void drawMask(const Mask& mask) const override;

protected:
    Position convertPosition(Position pos) const;
    PainterInterface& base_;
    CoordType dx_, dy_;

};

} // end namespace McuGui

#endif // PAINTER_H
