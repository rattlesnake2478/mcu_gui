#ifndef WIDGET_H
#define WIDGET_H

#include "painter.h"

#include <memory>
#include <vector>

namespace McuGui {

class AbstractWidget {
public:
    virtual void paint(PainterInterface& painter) const = 0;
};

class WidgetContainer: public AbstractWidget {
public:
    virtual void paint(PainterInterface& painter) const;
protected:
    struct Element {
        Position pos;
        const AbstractWidget* element;
    };

    void addElement(const AbstractWidget* el, Position pos) {
        elements_.push_back({pos, el});
    };
private:
    std::vector<Element> elements_;
};

} // end namespace McuiGui

#endif // WIDGET_H
