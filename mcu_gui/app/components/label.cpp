#include "label.h"

using namespace McuGui;

NumberLabel::NumberLabel(float val, FontType type, TextAlign align, bool float_mode)
    : AbstractLabel(val, type, align), float_mode_(float_mode) {}

std::string
NumberLabel::getStringData() const {
	uint32_t int_part = (uint32_t)val_;
	if (!float_mode_) {
		return std::to_string(int_part);
	}
	uint32_t float_part = (uint32_t)((val_ - int_part) * 100);
    return std::to_string(int_part) + std::string(".") + std::to_string(float_part);
};
