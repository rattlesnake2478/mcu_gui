#include "painter.h"

#include <cmath>
#include <utility>
#include <algorithm>

using namespace McuGui;

void
AbstractPainter::draw(Point point) {
    Position pos = point.pos() + origin_;
    if (pos.x >= 0 && pos.x < area_.w &&
        pos.y >= 0 && pos.y < area_.h) {
        plot(pos.x, pos.y, pen_);
    }
}

void
AbstractPainter::draw(const Mask& mask) {
    uint8_t shift = 0;
    uint8_t chunk = 0;
    for (uint16_t i = 0; i < mask.width; ++i)
        for (uint16_t j = 0; j < mask.height; ++j) {
            if((1 << (31 - shift)) & mask.data[chunk]) draw(Point(j, i));
            ++shift;
            if (shift >= 32) {
                shift = 0;
                ++chunk;
            }
            if (chunk >- mask.data.size()) return;
        }
}

void
GeometricPainter::draw(Line line) {
    bool steep = false;
    if (std::abs(line.start.x-line.end.x) < std::abs(line.start.y-line.end.y)) {
        std::swap(line.start.x, line.start.y);
        std::swap(line.end.x, line.end.y);
        steep = true;
    }
    if (line.start.x > line.end.x) {
        std::swap(line.start.x, line.end.x);
        std::swap(line.start.y, line.end.y);
    }
    CoordType dx = line.end.x - line.start.x;
    CoordType dy = line.end.y - line.start.y;
    CoordType derror2 = std::abs(dy)*2;
    CoordType error2 = 0;
    CoordType y = line.start.y;
    for (CoordType x = line.start.x; x <= line.end.x; x++) {
        if (steep) {
            draw(Point(y, x));
        } else {
            draw(Point(x, y));
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (line.end.y > line.start.y ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void
GeometricPainter::draw(Triangle triangle) {
    auto v1 = triangle.p1.pos();
    auto v2 = triangle.p2.pos();
    auto v3 = triangle.p3.pos();

    if (v1.y==v2.y && v1.y==v3.y) return;
    if (v1.y>v2.y) std::swap(v1, v2);
    if (v1.y>v3.y) std::swap(v1, v3);
    if (v2.y>v3.y) std::swap(v2, v3);

    CoordType total_height = v3.y-v1.y;
    for (CoordType i=0; i<total_height; i++) {
        bool second_half = i>v2.y-v1.y || v2.y==v1.y;
        CoordType segment_height = second_half ? v3.y-v2.y : v2.y-v1.y;
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? v2.y-v1.y : 0))/segment_height;
        Position A =               v1 + (v3-v1)*alpha;
        Position B = second_half ? v2 + (v3-v2)*beta : v1 + (v2-v1)*beta;
        if (A.x>B.x) std::swap(A, B);
        for (CoordType j=A.x; j<=B.x; j++) {
            Point p;
            p.x = j;
            p.y = v1.y+i;
            draw(p);
        }
    }
}

void
GeometricPainter::draw(Rectangle rectangle) {
    for (CoordType y = rectangle.top_left.y; y <= rectangle.bottom_right.y; ++y) {
        for(CoordType x = rectangle.top_left.x; x <= rectangle.bottom_right.x; ++x) {
            draw(Point(x, y));
        }
    }
}

void
MemoryPainter::
plot(CoordType x, CoordType y, Color color) {
  ptr_[y * area_.w + x] = color;
}

