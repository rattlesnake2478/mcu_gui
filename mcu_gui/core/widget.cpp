#include "widget.h"

using namespace McuGui;

void
WidgetContainer::paint(AbstractPainter& painter) const {
    Position origin = painter.getLocalOrigin();
    for (const auto& element: elements_) {
        painter.setLocalOrigin(origin + element.pos);
        element.element->paint(painter);
    }
}
