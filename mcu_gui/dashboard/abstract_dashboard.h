#ifndef ABSTRACT_DASHBOARD_H
#define ABSTRACT_DASHBOARD_H

#include "../../core/widget.h"

namespace McuGui {

template<typename T> class AbstractDashboard
{
public:
    virtual void paint(SimplePainter& pnt) const = 0;
    virtual T& getValues();

protected:
    T values;
};

}


#endif // ABSTRACT_DASHBOARD_H
