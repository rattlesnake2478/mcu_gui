#include "digit_segment.h"

using namespace McuGui;

void
DigitSegment::paint(PainterInterface& painter) const {
    const auto dim = DigitSegment::getSize(size_);

    // vertexes
    Position p1{(CoordType)(-dim.w/2),(CoordType)(-dim.h/2 + dim.w/2)};
    Position p2{0, (CoordType)(-dim.h/2)};
    Position p3{(CoordType)(dim.w/2), (CoordType)(-dim.h/2 + dim.w/2)};
    Position p4{(CoordType)(dim.w/2), (CoordType)(dim.h/2 - dim.w/2)};
    Position p5{0, (CoordType)(dim.h/2)};
    Position p6{(CoordType)(-dim.w/2), (CoordType)(dim.h/2 - dim.w/2)};

    // swap coordinates for horizontal layout
    if (type_ == Type::Horizontal) {
        p1.swapCoord();
        p2.swapCoord();
        p3.swapCoord();
        p4.swapCoord();
        p5.swapCoord();
        p6.swapCoord();
    }

    // body
    painter.setPen(color_);
    painter.drawTriangle(p1, p2, p3);
    painter.drawTriangle(p1, p3, p4);
    painter.drawTriangle(p1, p6, p4);
    painter.drawTriangle(p4, p5, p6);

    // border
    painter.setPen(border_);
    painter.drawLine(p1, p2);
    painter.drawLine(p2, p3);
    painter.drawLine(p3, p4);
    painter.drawLine(p4, p5);
    painter.drawLine(p5, p6);
    painter.drawLine(p6, p1);

};
