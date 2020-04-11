#include "paint_engine.h"

using namespace McuGui;

void
MemoryPaintEngine::plot(CoordType x, CoordType y, Color color) const {
    if (x >= 0 && x < area_.w && y >= 0 && y < area_.h) ptr_[y * area_.w + x] = color;
}

void
MemoryPaintEngine::copyBitmap(CoordType x, CoordType y, Bitmap b) const {
    if (x < 0 && x >= area_.w && y < 0 && y >= area_.h) return; // out of bounds
    Color* it = ptr_ + (y * area_.w + x);

    SizeType row_max = y + b.size.h >= area_.h ? area_.h - y : b.size.h;
    SizeType col_max = x + b.size.w >= area_.w ? area_.w - x : b.size.w;
    SizeType col_gap = x + b.size.w >= area_.w ? x : area_.w - b.size.w;

    for (SizeType row = 0; row < row_max; ++row) {
        for (SizeType col = 0; col < col_max; ++col) {
            *it++ = b.data[col + row * b.size.w];
        }
        it += col_gap;
    }
};
