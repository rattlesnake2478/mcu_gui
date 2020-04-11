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
    virtual void drawBitmap(Position pos, Bitmap bitmap) const = 0;
};

class SimplePainter: public PainterInterface {
public:
    SimplePainter(PaintEngineInterface& engine): engine_(engine) {};

    virtual void setPen(Color color) override { pen_ = color; };

    virtual void drawPoint(Position pos) const override;
    virtual void drawLine(Position start, Position end) const override;
    virtual void drawTriangle(Position v1, Position v2, Position v3) const override;
    virtual void drawMask(const Mask& mask) const override;
    virtual void drawBitmap(Position pos, Bitmap bitmap) const override;

protected:
    const PaintEngineInterface& engine_;
    Color pen_ = COLOR_WHITE;
};

class PainterDecorator: public PainterInterface {
public:
    PainterDecorator(PainterInterface& base): base_(base) {}

    // coloring
    virtual void setPen(Color color) override { base_.setPen(color); };

    // drawing
    virtual void drawPoint(Position pos) const override;
    virtual void drawLine(Position start, Position end) const override;
    virtual void drawTriangle(Position v1, Position v2, Position v3) const override;
    virtual void drawMask(const Mask& mask) const override;
    virtual void drawBitmap(Position pos, Bitmap bitmap) const override;

protected:
    virtual Position convertPosition(Position pos) const = 0;
    PainterInterface& base_;
};

class MovedPainter: public PainterDecorator {
public:
    MovedPainter(PainterInterface& base, CoordType dx, CoordType dy)
        : PainterDecorator(base), dx_(dx), dy_(dy) {}

protected:
    Position convertPosition(Position pos) const;
    CoordType dx_, dy_;

};


class TransformedPainter: public PainterInterface {
public:
    TransformedPainter(PainterInterface& base, FloatMatrix transform)
        : base_(base), transform_(transform) {}

    // coloring
    virtual void setPen(Color color) override { base_.setPen(color); };

    // drawing
    virtual void drawPoint(Position pos) const override;
    virtual void drawLine(Position start, Position end) const override;
    virtual void drawTriangle(Position v1, Position v2, Position v3) const override;
    virtual void drawMask(const Mask& mask) const override;
    virtual void drawBitmap(Position pos, Bitmap bitmap) const override;

protected:
    PainterInterface& base_;
    FloatMatrix transform_;

};

} // end namespace McuGui

#endif // PAINTER_H
