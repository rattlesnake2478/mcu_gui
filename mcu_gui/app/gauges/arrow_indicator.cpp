#include "arrow_indicator.h"
#include "../components/label.h"
#include "segment_indicator.h"

using namespace McuGui;

ArrowIndicator::ArrowIndicator(
        Bitmap bgrnd,
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
        bool float_mode)
    : bgrnd_(bgrnd),
      min_val_(min_val),
      val_scale_(max_val - min_val),
      min_angle_(min_angle),
      angle_scale_(max_angle - min_angle),
      center_(center),
      radius_(radius),
      label_pos_(label_pos),
      val_(min_val),
      label_color_(label_color),
      arrow_color_(arrow_color),
      label_(min_val, type, align, float_mode)
{};

void
ArrowIndicator::setValue(float value) {
    label_.setValue(value);
    if (value < min_val_) val_ = min_val_;
    else if (value > min_val_ + val_scale_) val_ = min_val_ + val_scale_;
    else val_ = value;
}

void
ArrowIndicator::paint(PainterInterface &painter) const {
    painter.drawBitmap({0, 0}, bgrnd_);
    painter.setPen(label_color_);
    MovedPainter pnt(painter, label_pos_.x, label_pos_.y);
    label_.paint(pnt);

    // draw arrow
    float angle = min_angle_ + (val_ - min_val_) / val_scale_ * angle_scale_;
    TransformedPainter pnt2(painter, TransformMatrix::move(radius_, 0) * TransformMatrix::rotate(angle) * TransformMatrix::move(center_.x, center_.y));
    pnt2.setPen(arrow_color_);
    pnt2.drawTriangle({0, 0}, {-40, -10}, {-30, 0});
    pnt2.drawTriangle({0, 0}, {-40, 10}, {-30, 0});

};

ArrowIndicator ArrowIndicator::buildArrowA(Bitmap bgrng, float min_val, float max_val, bool float_mode) {
    return ArrowIndicator(bgrng, min_val, max_val, 170, 100, {85, 85}, 85, COLOR_WHITE, COLOR_LIGHT_MAGENTA, VERDANA_NUMBER_20, ALIGN_RIGHT, {83, 60}, float_mode);
}
