#ifndef TACHOMETER_H
#define TACHOMETER_H

#include "gauge.h"

namespace McuGui {

// this is special class for type 1 tachometer
class TachometerTyp1: public AbstractGauge<uint16_t> {
public:
    TachometerTyp1(Bitmap bgrnd): AbstractGauge(), bgrnd_(bgrnd) {}
    virtual void paint(PainterInterface& painter) const override;
    virtual void setValue(uint16_t value) override;
protected:
    Bitmap bgrnd_;
};

} // end namespace McuGui

#endif // TACHOMETER_H
