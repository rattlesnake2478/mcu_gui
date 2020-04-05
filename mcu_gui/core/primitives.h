#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "types.h"

#include <vector>

namespace McuGui {

    struct Point {
        CoordType x;
        CoordType y;
        Point(CoordType x, CoordType y): x(x), y(y) {};
        explicit Point (Position pos): x(pos.x), y(pos.y) {};
    };

    struct Line {
        Position start;
        Position end;
        Line(Position start, Position end): start(start), end(end) {};
    };

    struct Triangle {
        Position p1;
        Position p2;
        Position p3;
        Triangle(Position p1, Position p2, Position p3): p1(p1), p2(p2), p3(p3) {};
    };

    struct Mask {
        uint16_t width;
        uint16_t height;
        std::vector<uint32_t> data;

        Mask(uint16_t w, uint16_t h, std::vector<uint32_t> v):width(w), height(h), data(v) {};
    };

} //end namespace McuGui

#endif // PRIMITIVES_H
