#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

namespace mcugui {

typedef int16_t CoordType;
typedef uint16_t LenType;

enum PixelFormat {
    ARGB32 = 0,
    RGB24,
    RGB565,
    RGB555,
    CLUT8
};

struct Point {
    CoordType x;
    CoordType y;

    template <typename T>
    Point operator+(T&& other) const {
        CoordType res_x = x + other.x;
        CoordType res_y = y + other.y;
        return {res_x, res_y};
    }

    template <typename T>
    Point operator-(T&& other) const {
        CoordType res_x = x - other.x;
        CoordType res_y = y - other.y;
        return {res_x, res_y};
    }

    Point operator*(float value) const {
        CoordType res_x = (CoordType)x*value;
        CoordType res_y = (CoordType)y*value;
        return {res_x, res_y};
    }
};

struct Rect {
    CoordType x;
    CoordType y;
    LenType width;
    LenType height;

    inline CoordType right() const { return x + width; }
    inline CoordType bottom() const { return y + height; }

    bool intersect(const Rect& other) const {
      return !(x >= other.right() || right() <= other.x || y >= other.bottom() || bottom() <= other.y);
    }

    inline Rect& moveTo(Point point) {
      x = point.x;
      y = point.y;
      return *this;
    }

    inline Point getOrigin() {
      return {x, y};
    }
};

} // end namespace mcugui

#endif // TYPES_H
