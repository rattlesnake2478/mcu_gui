#ifndef PAINT_ENGINE_H
#define PAINT_ENGINE_H

#include "types.h"

namespace McuGui {

class PaintEngineInterface {
public:
    virtual void plot(CoordType x, CoordType y, Color c) const = 0;
    virtual void copyBitmap(CoordType x, CoordType y, Bitmap b) const = 0;
};

class MemoryPaintEngine: public PaintEngineInterface {
public:
    explicit MemoryPaintEngine(Color* ptr, Dimension area = DEFAULT_DISPLAY): ptr_(ptr), area_(area) {};
    virtual void plot(CoordType x, CoordType y, Color c) const override;
    virtual void copyBitmap(CoordType x, CoordType y, Bitmap b) const override;

protected:
    Color* const ptr_;
    Dimension area_;
};

} // end namespace McuGui

#endif // PAINT_ENGINE_H
