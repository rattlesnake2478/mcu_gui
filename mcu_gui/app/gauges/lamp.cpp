#include "lamp.h"

using namespace McuGui;

const Dimension Lamp::StandartDimension = {40, 40};

void
Lamp::paint(PainterInterface& painter) const {
    // Draw lamp base
    painter.setPen(value_ ? active_color_ : inactive_color_);

    switch (type_) {
        case Type::SQARE:
            painter.drawTriangle({0, 0}, {0, 40}, {40, 40});
            painter.drawTriangle({0, 0}, {40, 0}, {40, 40});
        break;
    }
    painter.setPen(value_ ? active_glyph_color_ : inactive_glyph_color_);
    MovedPainter pnt(painter, 5, 5);
    pnt.drawMask(glyph_);
};
