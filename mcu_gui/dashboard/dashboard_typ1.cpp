#include "dashboard_typ1.h"

using namespace McuGui;

DashboardType1::DashboardType1(Bitmap tach, Bitmap volt, Bitmap temp):
    ltl_(),
    rtl_(),
    nl_(),
    hbl_(),
    bl_(),
    tl_(),
    speed_(DigitSegment::Huge, COLOR_BLUE, COLOR_WHITE),
    temp_(ArrowIndicator::buildArrowA(temp, 60, 130, false)),
    volt_(ArrowIndicator::buildArrowA(volt, 10, 18, true)),
    time_(),
    tach_(tach),
    l_lamps_(Lamp::StandartDimension, 3, 5),
    r_lamps_(Lamp::StandartDimension, 3, 5)
{
    l_lamps_.addWidget(&ltl_, 0);
    l_lamps_.addWidget(&nl_, 1);
    l_lamps_.addWidget(&bl_, 2);
    r_lamps_.addWidget(&tl_, 0);
    r_lamps_.addWidget(&hbl_, 1);
    r_lamps_.addWidget(&rtl_, 2);
}

void
DashboardType1::paint(PainterInterface &painter) const {
    MovedPainter pnt(painter, 0, 0);
    // draw lamps and time - upper line
    pnt.move(-5, 0);
    l_lamps_.paint(pnt);
    pnt.move(175, 0);
    time_.paint(pnt);
    pnt.move(164, 0);
    r_lamps_.paint(pnt);

    // draw speedometer
    pnt.move(131, 260);
    speed_.paint(pnt);

    // draw temp
    pnt.move(-350, -80);
    temp_.paint(pnt);

    // draw volt
    pnt.move(0, -90);
    volt_.paint(pnt);

    // draw tachometer
    pnt.move(-112, -45);
    tach_.paint(pnt);

}

void DashboardType1::setData(const Data& data) {
    ltl_.setValue(data.lamps.ltl);
    rtl_.setValue(data.lamps.rtl);
    nl_.setValue(data.lamps.nl);
    hbl_.setValue(data.lamps.hbl);
    bl_.setValue(data.lamps.bl);
    tl_.setValue(data.lamps.tl);

    if (data.speed > 199) speed_.setValue(199);
    else speed_.setValue(data.speed);

    temp_.setValue(data.temp);
    volt_.setValue(data.voltage);
    time_.setTime(data.hrs, data.min);
    tach_.setValue(data.tach);
}
