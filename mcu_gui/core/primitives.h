#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "types.h"

#include <vector>

namespace McuGui {

    struct Point {
        CoordType x;
        CoordType y;
        Point (): x(0), y(0) {};
        Point (CoordType x, CoordType y): x(x), y(y) {};
        explicit Point (Position pos): x(pos.x), y(pos.y) {};
        Position pos() const { return {x, y}; }
        Point swapCoords() const { return {y, x}; }
    };

    struct Line {
        Point start;
        Point end;
        Line(Point start, Point end): start(start), end(end) {};
    };

    struct Triangle {
        Point p1;
        Point p2;
        Point p3;
        Triangle(Point p1, Point p2, Point p3): p1(p1), p2(p2), p3(p3) {};
    };

    struct Rectangle {
        Point top_left;
        Point bottom_right;
        Rectangle(Point p1, Point p2) {
            top_left = {
                p1.x < p2.x ? p1.x : p2.x,
                p1.y < p2.y ? p1.y : p2.y
            };

            bottom_right = {
                p1.x > p2.x ? p1.x : p2.x,
                p1.y > p2.y ? p1.y : p2.y
            };
        };

        Rectangle(Point start, SizeType width, SizeType height): top_left(start) {
            bottom_right = {(CoordType)(start.x + width), (CoordType)(start.y + height)};
        }
    };

    struct Mask {
        uint16_t width;
        uint16_t height;
        std::vector<uint32_t> data;

        Mask(uint16_t w, uint16_t h, std::vector<uint32_t> v):width(w), height(h), data(v) {};
    };




} //end namespace McuGui

#endif // PRIMITIVES_H
