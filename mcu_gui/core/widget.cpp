#include "widget.h"

using namespace McuGui;

void
WidgetContainer::paint(PainterInterface& painter) const {
    for (const auto& element: elements_) {
        MovedPainter pnt(painter, element.pos.x, element.pos.y);
        element.element->paint(pnt);
    }
}
