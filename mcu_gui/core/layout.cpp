#include "layout.h"

using namespace McuGui;

Position
GridLayout::getPosition(uint8_t row, uint8_t col) const {
    CoordType x = (CoordType)((2 * margin_.w + cell_size_.w) * col + margin_.w);
    CoordType y = (CoordType)((2 * margin_.h + cell_size_.h) * row + margin_.h);
    return {x, y};
}
