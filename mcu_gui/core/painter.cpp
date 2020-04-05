#include "painter.h"

#include <cmath>
#include <utility>
#include <algorithm>

using namespace McuGui;

void
SimplePainter::drawPoint(Position pos) const {
    engine_.plot(pos.x, pos.y, pen_);
}

void
SimplePainter::drawMask(const Mask& mask) const {
    uint8_t shift = 0;
    uint8_t chunk = 0;
    for (uint16_t i = 0; i < mask.width; ++i) {
        for (uint16_t j = 0; j < mask.height; ++j) {
            if((1 << (31 - shift)) & mask.data[chunk]) drawPoint({(CoordType)j, (CoordType)i});
            ++shift;
            if (shift >= 32) {
                shift = 0;
                ++chunk;
            }
            if (chunk >- mask.data.size()) return;
        }
    }
}

void
SimplePainter::drawLine(Position start, Position end) const {
    bool steep = false;
    if (std::abs(start.x-end.x) < std::abs(start.y-end.y)) {
        std::swap(start.x, start.y);
        std::swap(end.x, end.y);
        steep = true;
    }
    if (start.x > end.x) {
        std::swap(start.x, end.x);
        std::swap(start.y, end.y);
    }
    CoordType dx = end.x - start.x;
    CoordType dy = end.y - start.y;
    CoordType derror2 = std::abs(dy)*2;
    CoordType error2 = 0;
    CoordType y = start.y;
    for (CoordType x = start.x; x <= end.x; x++) {
        if (steep) {
            drawPoint({y, x});
        } else {
            drawPoint({x, y});
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (end.y > start.y ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void
SimplePainter::drawTriangle(Position v1, Position v2, Position v3) const {
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
            drawPoint({j, (CoordType)(v1.y+i)});
        }
    }
}

void
PainterDecorator::drawPoint(Position pos) const {
    base_.drawPoint(convertPosition(pos));
}

void
PainterDecorator::drawLine(Position start, Position end) const {
    base_.drawLine(convertPosition(start), convertPosition(end));
}

void
PainterDecorator::drawTriangle(Position v1, Position v2, Position v3) const {
    base_.drawTriangle(convertPosition(v1), convertPosition(v2), convertPosition(v3));
}

void
PainterDecorator::drawMask(const Mask& mask) const {
    // copies original method. TODO: rework
    uint8_t shift = 0;
    uint8_t chunk = 0;
    for (uint16_t i = 0; i < mask.width; ++i) {
        for (uint16_t j = 0; j < mask.height; ++j) {
            if((1 << (31 - shift)) & mask.data[chunk]) drawPoint({(CoordType)j, (CoordType)i});
            ++shift;
            if (shift >= 32) {
                shift = 0;
                ++chunk;
            }
            if (chunk >- mask.data.size()) return;
        }
    }
}

Position
MovedPainter::convertPosition(Position pos) const {
    return {(CoordType)(pos.x + dx_), (CoordType)(pos.y + dy_)};
}

void
TransformedPainter::drawPoint(Position pos) const {
    auto vertexMatrix = FloatMatrix::fromVertexes({pos});
    auto result = (vertexMatrix * transform_).toVertexes();
    base_.drawPoint(result[0]);
}

void
TransformedPainter::drawLine(Position start, Position end) const {
    auto vertexMatrix = FloatMatrix::fromVertexes({start, end});
    auto result = (vertexMatrix * transform_).toVertexes();
    base_.drawLine(result[0], result[1]);
}

void
TransformedPainter::drawTriangle(Position v1, Position v2, Position v3) const {
    auto vertexMatrix = FloatMatrix::fromVertexes({v1, v2, v3});
    auto result = (vertexMatrix * transform_).toVertexes();
    base_.drawTriangle(result[0], result[1], result[2]);
}

void
TransformedPainter::drawMask(const Mask& mask) const {
    // copies original method. TODO: rework
    uint8_t shift = 0;
    uint8_t chunk = 0;
    for (uint16_t i = 0; i < mask.width; ++i) {
        for (uint16_t j = 0; j < mask.height; ++j) {
            if((1 << (31 - shift)) & mask.data[chunk]) drawPoint({(CoordType)j, (CoordType)i});
            ++shift;
            if (shift >= 32) {
                shift = 0;
                ++chunk;
            }
            if (chunk >- mask.data.size()) return;
        }
    }
}
