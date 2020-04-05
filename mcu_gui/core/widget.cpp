#include "widget.h"

using namespace McuGui;

void
WidgetContainer::paint(PainterInterface& painter) const {
    for (const auto& element: elements_) {
        element.element->paint(painter);
    }
}
