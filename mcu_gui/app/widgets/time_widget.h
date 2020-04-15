#ifndef TIME_WIDGET_H
#define TIME_WIDGET_H

#include "../../core/widget.h"
#include "../gauges/segment_indicator.h"

namespace McuGui {

class TimeWidget: public AbstractWidget {
public:
    TimeWidget(Color fill = COLOR_RED, Color border = COLOR_WHITE);
    void setTime(uint8_t hours, uint8_t minutes, bool tick = true);
    void paint(PainterInterface &painter) const override;
protected:
    uint8_t hours_;
    uint8_t minutes_;
    mutable SegmentIndicator ind_;
    const Color fill_;
    const Color border_;
    bool tick_; // flag for dots
};

} // end namespace McuGui
#endif // TIME_WIDGET_H
