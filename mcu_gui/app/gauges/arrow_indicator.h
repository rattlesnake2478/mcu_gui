#ifndef ARROW_GAUGE_H
#define ARROW_GAUGE_H

#include "../../core/widget.h"
#include "../components/label.h"

namespace McuGui {

// Complex class to tune. Use predefined static methods instead
class ArrowIndicator: public AbstractWidget {
public:
    ArrowIndicator(Bitmap bgrnd,
                   float min_val,
                   float max_val,
                   int16_t min_angle,
                   int16_t max_angle,
                   Position center,
                   CoordType radius,
                   Color label_color,
                   Color arrow_color,
                   FontType type,
                   TextAlign align,
                   Position label_pos,
                   bool float_mode);
    void paint(PainterInterface &painter) const override;
    void setValue(float value);

    static ArrowIndicator buildArrowA(Bitmap bgrng, float min_val, float max_val, bool float_mode);

protected:
    Bitmap bgrnd_;
    float min_val_;
    float val_scale_;
    int16_t min_angle_;
    int16_t angle_scale_;
    Position center_;
    CoordType radius_;
    Position label_pos_;
    float val_;
    Color label_color_;
    Color arrow_color_;
    NumberLabel label_;
};

} // end namespace McuGui

#endif // ARROW_GAUGE_H
