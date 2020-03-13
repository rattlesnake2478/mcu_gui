#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>

namespace McuGui {

typedef int16_t CoordType;
typedef uint16_t SizeType;

struct Position {
    CoordType x = 0;
    CoordType y = 0;
    Position operator+(const Position& other) const {
        CoordType res_x = x + other.x;
        CoordType res_y = y + other.y;
        return {res_x, res_y};
    }
    Position operator-(const Position& other) const {
        CoordType res_x = x - other.x;
        CoordType res_y = y - other.y;
        return {res_x, res_y};
    }
    Position operator*(float value) const {
        CoordType res_x = (CoordType)x*value;
        CoordType res_y = (CoordType)y*value;
        return {res_x, res_y};
    }
};

struct Dimension {
    SizeType w;
    SizeType h;
};

const Dimension DISPLAY_480_272 = {480, 272};
const Dimension DEFAULT_DISPLAY = DISPLAY_480_272;

} // end namespace McuGui

#endif // TYPES_H
