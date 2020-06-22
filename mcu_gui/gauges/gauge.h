#ifndef GAUGE_H
#define GAUGE_H

#include "../core/widget.h"

namespace McuGui {

template <class T> class AbstractGauge: public AbstractWidget {
public:
    virtual void paint(PainterInterface& painter) const override = 0;
    virtual void setValue(T value) { value_ = value; };
protected:
    T value_;
};

} // end namespace McuGui

#endif // GAUGE_H
