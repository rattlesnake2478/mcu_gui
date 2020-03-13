#include "digit_segment.h"

using namespace McuGui;

void
DigitSegment::paint(AbstractPainter &painter) const {
    const auto dim = DigitSegment::getSize(size_);

    // vertexes
    Point p1((CoordType)(-dim.w/2),(CoordType)(-dim.h/2 + dim.w/2));
    Point p2(0, (CoordType)(-dim.h/2));
    Point p3((CoordType)(dim.w/2), (CoordType)(-dim.h/2 + dim.w/2));
    Point p4((CoordType)(dim.w/2), (CoordType)(dim.h/2 - dim.w/2));
    Point p5(0, (CoordType)(dim.h/2));
    Point p6((CoordType)(-dim.w/2), (CoordType)(dim.h/2 - dim.w/2));

    // swap coordinates for horizontal layout
    if (type_ == Type::Horizontal) {
        p1 = p1.swapCoords();
        p2 = p2.swapCoords();
        p3 = p3.swapCoords();
        p4 = p4.swapCoords();
        p5 = p5.swapCoords();
        p6 = p6.swapCoords();
    }

    // body
    painter.setPen(color_);
    painter.draw(Triangle(p1, p2, p3));
    painter.draw(Rectangle(p1, p4));
    painter.draw(Triangle(p4, p5, p6));

    // border
    painter.setPen(border_);
    painter.draw(Line(p1, p2));
    painter.draw(Line(p2, p3));
    painter.draw(Line(p3, p4));
    painter.draw(Line(p4, p5));
    painter.draw(Line(p5, p6));
    painter.draw(Line(p6, p1));

};
