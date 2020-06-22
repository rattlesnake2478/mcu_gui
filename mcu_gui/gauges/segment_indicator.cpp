#include "segment_indicator.h"

using namespace McuGui;

constexpr std::array<SegmentIndicator::SegmentMap, 10> SegmentIndicator::VAL_TO_SEGMENTS;

void
SegmentIndicator::paint(PainterInterface& painter) const {
    uint8_t value = value_ > 9 ? 9 : value_;
    for(const auto& segment: VAL_TO_SEGMENTS[value]) {
        if ( segment >= SegmentType::A && segment <= SegmentType::G) {
            drawSegment(painter, segment);
        }
    }
}

void
SegmentIndicator::drawSegment(PainterInterface& painter, SegmentType segment) const {
    Position segment_pos;
    const DigitSegment *segment_ptr;
    const auto dim = DigitSegment::getSize(size_);
    const CoordType gap = dim.w / 3 - 2;

    switch (segment) {
    case A:
        segment_ptr = &horiz_;
        segment_pos = {
            (CoordType)(-dim.h/2 - dim.w/2 - gap),
            (CoordType)(-dim.w/2 - gap * 4 - dim.h * 2)
        };
    break;
    case B:
        segment_ptr = &vert_;
        segment_pos = {(CoordType)(-dim.w/2), (CoordType)(-dim.w/2 - gap * 3 - dim.h - dim.h/2)};

    break;
    case C:
        segment_ptr = &vert_;
        segment_pos = {(CoordType)(-dim.w/2), (CoordType)(-dim.w/2 - gap - dim.h/2)};
    break;
    case D:
        segment_ptr = &horiz_;
        segment_pos = {(CoordType)(-dim.h/2 - dim.w/2 - gap), (CoordType)(-dim.w/2)};
    break;
    case E:
        segment_ptr = &vert_;
        segment_pos = {(CoordType)(-dim.w/2 - gap*2 - dim.h), (CoordType)(-dim.w/2 - gap - dim.h/2)};
    break;
    case F:
        segment_ptr = &vert_;
        segment_pos = {(CoordType)(-dim.w/2 - gap*2 - dim.h), (CoordType)(-dim.w/2 - gap * 3 - dim.h - dim.h/2)};
    break;
    case G:
        segment_ptr = &horiz_;
        segment_pos = {
            (CoordType)(-dim.h/2 - dim.w/2 - gap),
            (CoordType)(-dim.w/2 - gap*2  - dim.h)
        };
    break;
    }
    MovedPainter pnt(painter, segment_pos.x, segment_pos.y);
    segment_ptr->paint(pnt);
}

void
MultiSegmentIndicator::paint(PainterInterface& painter) const {
    uint16_t next_value = std::abs(value_);
    uint8_t offset_pos = 0;
    const auto segment_dim = DigitSegment::getSize(size_);
    CoordType offset = segment_dim.w * 3 + segment_dim.h;
    uint8_t segment_value;
    do {
        segment_value = next_value % 10;
        next_value = next_value / 10;
        indicator_.setValue(segment_value);
        MovedPainter pnt(painter, (CoordType)(-offset * offset_pos), 0);
        indicator_.paint(pnt);
        ++offset_pos;
    } while (next_value);
    if (value_ < 0) {
        CoordType dash_x_offset = segment_value == 1 ? offset * offset_pos - segment_dim.w * 2 : offset * offset_pos + segment_dim.w;
        MovedPainter pnt(painter, - dash_x_offset, (CoordType)(-segment_dim.h - segment_dim.w));
        dash_.paint(pnt);
    }
}


