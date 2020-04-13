#include "label.h"

using namespace McuGui;

NumberLabel::NumberLabel(float val, FontType type, TextAlign align, bool float_mode)
    : AbstractLabel(val, type, align), float_mode_(float_mode) {}

std::string
NumberLabel::getStringData() const {
    std::string result = std::to_string(val_);
    auto pos = result.find('.');
    if (float_mode_) {
        return result.substr(0, pos + 3);
    }
    return result.substr(0, pos);
};
