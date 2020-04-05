#include "paint_engine.h"

using namespace McuGui;

void
MemoryPaintEngine::plot(CoordType x, CoordType y, Color color) const {
    if (x >= 0 && x < area_.w && y >= 0 && y < area_.h) ptr_[y * area_.w + x] = color;
}
