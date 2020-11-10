#include "paint_device.h"

using namespace McuGui;

template <typename ColorFormat>
void
MemoryPaintDevice<ColorFormat>::
plot(Position pos, value_type c) {
  if (
       pos.x >= 0 && pos.x < area_.w
    && pos.y >= 0 && pos.y < area_.h
  ) ptr_[pos.y * area_.w + pos.x] = c;
}

template <typename ColorFormat>
void
MemoryPaintDevice<ColorFormat>::
copyBitmap(Position pos, bitmap_type b) {
    copyData(pos, b.size, [b](SizeType row, SizeType col, value_type c) {
        size_t addr = col + row * b.size.w;
        return ColorFormat::mix(b.data[addr], c);
    });
}

template <typename ColorFormat>
void
MemoryPaintDevice<ColorFormat>::
fillRegion(Position pos, Dimension size, value_type c) {
    copyData(pos, size, [c](SizeType, SizeType, value_type) {
        return c;
    });
}

template <typename ColorFormat>
bool
MemoryPaintDevice<ColorFormat>::
isOutOfBounds(Position pos, Dimension size) const {
    if (pos.x >= area_.w || pos.y >= area_.h) return true;
    if (pos.x + size.w < 0 || pos.y + size.h < 0) return true;
    return false;
}

template <typename ColorFormat>
typename MemoryPaintDevice<ColorFormat>::region_type
MemoryPaintDevice<ColorFormat>::
getDrawableArea(Position pos, Dimension size) const {
    CoordType x_left = pos.x < 0 ? 0 : pos.x;
    CoordType y_top = pos.y < 0 ? 0 : pos.y;
    CoordType x_right = pos.x + size.w >= area_.w ? area_.w - 1 : pos.x + size.w;
    CoordType y_bottom = pos.y + size.h >= area_.h ? area_.h - 1 : pos.y + size.h;

    value_type *start = ptr_ + (y_top * area_.w + x_left);
    value_type *end = ptr_ + (y_bottom * area_.w + x_right);

    SizeType row_start = pos.y < 0 ? - pos.y : 0;
    SizeType row_end = pos.y + size.h >= area_.h ? area_.h - pos.y : size.h;
    SizeType col_start = pos.x < 0 ? - pos.x : 0;
    SizeType col_end = pos.x + size.w >= area_.w ? area_.w - pos.x : size.w;
    SizeType col_gap = area_.w + col_start - col_end;

    return {
        start,
        end,
        row_start,
        row_end,
        col_start,
        col_end,
        col_gap,
    };
}

template<typename ColorFormat>
template<typename F>
void
MemoryPaintDevice<ColorFormat>::
copyData(Position pos, Dimension size, F func) {
    if (isOutOfBounds(pos, size)) return;

    auto drawable = getDrawableArea(pos, size);
    auto it = drawable.start;

    for (SizeType row = drawable.row_start; row < drawable.row_end; ++row) {
        for (SizeType col = drawable.col_start; col < drawable.col_end; ++col) {
            auto val = func(row, col, *it);
            if (!ColorFormat::isTransparent(val)) {
                *it = val;
            }
            if(it != drawable.end) ++it;
        }
        if (row < drawable.row_end - 1) it += drawable.col_gap;
    }
}
