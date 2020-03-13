#ifndef WIDGET_H
#define WIDGET_H

#include "painter.h"

#include <memory>
#include <vector>

namespace McuGui {

class AbstractWidget {
public:
    virtual void paint(AbstractPainter& painter) const = 0;
};

class WidgetContainer: public AbstractWidget {
public:
    virtual void paint(AbstractPainter& painter) const;
protected:
    typedef std::shared_ptr<AbstractWidget> ElementPtr;
    struct Element {
        Position pos;
        ElementPtr element;
    };

    template<class T> void addElement(T t, Position pos) {
        elements_.push_back({pos, std::make_shared<T>(t)});
    };
private:
    std::vector<Element> elements_;

};

} // end namespace McuiGui

#endif // WIDGET_H
