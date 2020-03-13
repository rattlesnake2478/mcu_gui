#ifndef SEGMENTINDICATOR_H
#define SEGMENTINDICATOR_H

#include "../../core/gauge.h"
#include "../components/digit_segment.h"

namespace McuGui {

class SegmentIndicator: public AbstractGauge<uint8_t> {
public:
    SegmentIndicator(
            DigitSegment::Size size = DigitSegment::Mid,
            Color color = COLOR_RED,
            Color border = COLOR_WHITE
        ):
        size_(size),
        vert_(DigitSegment(DigitSegment::Vertical, size,  color, border)),
        horiz_(DigitSegment(DigitSegment::Horizontal, size, color, border)) {};
    virtual void paint(AbstractPainter& painter) const override;

protected:
    // segment definition and map
    enum SegmentType { A = 1, B, C, D, E, F, G };
    //    A
    //  F   B
    //    G
    //  E   C
    //    D
    using SegmentMap = std::array<SegmentType, 7>;
    constexpr static SegmentMap D0 = {SegmentType::A, SegmentType::B, SegmentType::C, SegmentType::D, SegmentType::E, SegmentType::F};
    constexpr static SegmentMap D1 = {SegmentType::B, SegmentType::C};
    constexpr static SegmentMap D2 = {SegmentType::A, SegmentType::B, SegmentType::G, SegmentType::E, SegmentType::D};
    constexpr static SegmentMap D3 = {SegmentType::A, SegmentType::B, SegmentType::G, SegmentType::C, SegmentType::D};
    constexpr static SegmentMap D4 = {SegmentType::F, SegmentType::G, SegmentType::B, SegmentType::C};
    constexpr static SegmentMap D5 = {SegmentType::A, SegmentType::F, SegmentType::G, SegmentType::C, SegmentType::D};
    constexpr static SegmentMap D6 = {SegmentType::A, SegmentType::F, SegmentType::G, SegmentType::C, SegmentType::D, SegmentType::E};
    constexpr static SegmentMap D7 = {SegmentType::A, SegmentType::B, SegmentType::C};
    constexpr static SegmentMap D8 = {SegmentType::A, SegmentType::B, SegmentType::C, SegmentType::D, SegmentType::E, SegmentType::F, SegmentType::G};
    constexpr static SegmentMap D9 = {SegmentType::A, SegmentType::F, SegmentType::G, SegmentType::B, SegmentType::C, SegmentType::D};
    constexpr static std::array<SegmentMap, 10> VAL_TO_SEGMENTS = {D0, D1, D2, D3, D4, D5, D6, D7, D8, D9};

    void drawSegment(AbstractPainter& painter, SegmentType segment) const;

    DigitSegment::Size size_;
    DigitSegment vert_;
    DigitSegment horiz_;
};

class MultiSegmentIndicator: public AbstractGauge<int16_t> {
public:
    MultiSegmentIndicator(
            DigitSegment::Size size = DigitSegment::Mid,
            Color color = COLOR_RED,
            Color border = COLOR_WHITE
        ):
        size_(size),
        indicator_(SegmentIndicator(size, color, border)),
        dash_(DigitSegment(DigitSegment::Horizontal, size,  color, border)) {};
    virtual void paint(AbstractPainter& painter) const override;
protected:
    DigitSegment::Size size_;
    mutable SegmentIndicator indicator_;
    DigitSegment dash_;
};

} // end namespace McuGui


#endif // SEGMENTINDICATOR_H
