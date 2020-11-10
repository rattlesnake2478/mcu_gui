#ifndef PAINT_DEVICE_H
#define PAINT_DEVICE_H

#include "../types.h"

namespace McuGui {

template <typename ColorFormat> class AbstractPaintDevice {
public:
    using value_type = typename ColorFormat::data_type;

    using bitmap_type = struct {
        value_type const * data;
        Dimension size;
    };

    virtual void plot(Position pos, value_type c) = 0;
    virtual void copyBitmap(Position pos, bitmap_type bitmap) = 0;
    virtual void fillRegion(Position pos, Dimension size, value_type c) = 0;
};

template <typename ColorFormat> class MemoryPaintDevice: public AbstractPaintDevice<ColorFormat> {
public:
    using value_type = typename AbstractPaintDevice<ColorFormat>::value_type;
    using bitmap_type = typename AbstractPaintDevice<ColorFormat>::bitmap_type;

    MemoryPaintDevice(value_type * const ptr, Dimension size): ptr_(ptr), area_(size) {};
    virtual void plot(Position pos, value_type c);
    virtual void copyBitmap(Position pos, bitmap_type bitmap);
    virtual void fillRegion(Position pos, Dimension size, value_type c);

protected:
    using region_type = struct {
        value_type* start;
        value_type* end;
        SizeType row_start;
        SizeType row_end;
        SizeType col_start;
        SizeType col_end;
        SizeType col_gap;
    };

    bool isOutOfBounds(Position pos, Dimension size) const;
    region_type getDrawableArea(Position pos, Dimension size) const;
    template<typename F> void copyData(Position pos, Dimension size, F func);

    value_type * const ptr_;
    Dimension area_;
};

} // end namespace McuGui


#endif // PAINT_DEVICE_H
