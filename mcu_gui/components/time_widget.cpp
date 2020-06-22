#include "time_widget.h"

using namespace McuGui;

TimeWidget::TimeWidget(Color fill, Color border)
    :fill_(fill), border_(border)
{
    hours_ = 0;
    minutes_ = 0;
    ind_ = SegmentIndicator(DigitSegment::Small, fill_, border_);
};

void
TimeWidget::setTime(uint8_t hours, uint8_t minutes, bool tick) {
    if(hours > 23) hours = 23;
    if(minutes > 59) minutes = 59;
    hours_ = hours;
    minutes_ = minutes;
    tick_ = tick;
}

void
TimeWidget::paint(PainterInterface &painter) const {
    CoordType step = 30;
    MovedPainter pnt(painter, step, 45);

    ind_.setValue(hours_ / 10);
    ind_.paint(pnt);
    pnt.move(step, 0);

    ind_.setValue(hours_ % 10);
    ind_.paint(pnt);
    pnt.move(step, 0);

    if(tick_) {
        MovedPainter dotPainter(pnt, -step/2 - 5, -step);
        dotPainter.setPen(fill_);
        dotPainter.drawTriangle({0, 0}, {4, 0}, {0, 4});
        dotPainter.drawTriangle({0, 4},{4, 0}, {4, 4});
        dotPainter.setPen(border_);
        dotPainter.drawLine({1, 0}, {3, 0});
        dotPainter.drawLine({4, 1}, {4, 3});
        dotPainter.drawLine({3, 4}, {1, 4});
        dotPainter.drawLine({0, 3}, {0, 1});
        dotPainter.move(0, step/2);
        dotPainter.setPen(fill_);
        dotPainter.drawTriangle({0, 0}, {4, 0}, {0, 4});
        dotPainter.drawTriangle({0, 4},{4, 0}, {4, 4});
        dotPainter.setPen(border_);
        dotPainter.drawLine({1, 0}, {3, 0});
        dotPainter.drawLine({4, 1}, {4, 3});
        dotPainter.drawLine({3, 4}, {1, 4});
        dotPainter.drawLine({0, 3}, {0, 1});
    }
    pnt.move(step / 2, 0);

    ind_.setValue(minutes_ / 10);
    ind_.paint(pnt);
    pnt.move(step, 0);

    ind_.setValue(minutes_ % 10);
    ind_.paint(pnt);
    pnt.move(step, 0);
};
