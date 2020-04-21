#ifndef DASHBOARD_TYP1_H
#define DASHBOARD_TYP1_H

#include "../../core/widget.h"
#include "../gauges/arrow_indicator.h"
#include "../gauges/lamp.h"
#include "../gauges/tachometer.h"
#include "../widgets/time_widget.h"

namespace McuGui {

class DashboardType1: public AbstractWidget {
public:
    struct Data {
        uint16_t tach = 0;
        float voltage = 0;
        float temp = 0;
        uint8_t speed = 0;
        uint8_t hrs = 0;
        uint8_t min = 0;
        struct {
            bool ltl:1;
            bool rtl:1;
            bool nl:1;
            bool hbl:1;
            bool bl:1;
            bool tl:1;
        } lamps;
    };
    DashboardType1(Bitmap tach, Bitmap volt, Bitmap temp);
    void paint(PainterInterface &painter) const override;
    void setData(const Data& data);

private:
    LeftTurnLamp ltl_;
    RightTurnLamp rtl_;
    NeutralLamp nl_;
    HighBeamLamp hbl_;
    BatteryLamp bl_;
    TempLamp tl_;
    MultiSegmentIndicator speed_;
    ArrowIndicator temp_;
    ArrowIndicator volt_;
    TimeWidget time_;
    TachometerTyp1 tach_;
};

} // end namespace McuGui


#endif // DASHBOARD_TYP1_H
