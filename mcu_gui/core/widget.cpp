#include "widget.h"

using namespace McuGui;

void
WidgetContainer::paint(AbstractPainter& painter) const {
    for (const auto& element: elements_) {
        painter.setLocalOrigin(element.pos);
        element.element->paint(painter);
    }
}
