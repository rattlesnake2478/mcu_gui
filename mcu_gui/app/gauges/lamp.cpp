#include "lamp.h"

using namespace McuGui;

void
Lamp::paint(AbstractPainter& painter) const {
    // Draw lamp base
    painter.setPen(value_ ? active_color_ : inactive_color_);

    switch (type_) {
        case Type::SQARE:
            painter.draw(Rectangle({0, 0}, {40, 40}));
        break;
    }
    painter.setPen(value_ ? active_glyph_color_ : inactive_glyph_color_);
    painter.setLocalOrigin(painter.getLocalOrigin() + Position({4, 4}));
    painter.draw(glyph_);
};
