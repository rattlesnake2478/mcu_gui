#include "color.h"

using namespace mcugui;

uint32_t
Color::
getValue(PixelFormat format) {
    switch (format) {
        case PixelFormat::RGB24:
            return convertToRgb24();
        case PixelFormat::RGB565:
            return convertToRgb565();
        case PixelFormat::RGB555:
            return convertToRgb565();
        case PixelFormat::CLUT8:
            return convertToClut8();
        case PixelFormat::ARGB32:
        default:
            return value_;
    }
}

uint8_t
Color::
getAlpha() const {
    return (uint8_t)((0xff000000U & value_) >> 24);
}

uint8_t
Color::
getRed() const {
    return (uint8_t)((0xff0000U & value_) >> 16);
}

uint8_t
Color::
getGreen() const {
    return (uint8_t)((0xff00U & value_) >> 8);
}

uint8_t
Color::
getBlue() const {
    return (uint8_t)(0xffU & value_);
}

uint32_t
Color::
convertToRgb24() const {
    return 0x00FFFFFF & value_; // just clear alpha channel
}

uint32_t
Color::
convertToRgb565() const {
    //TODO: implement
    return value_;
}

uint32_t
Color::
convertToRgb555() const {
    //TODO: implement
    return value_;
}
uint32_t
Color::
convertToClut8() const {
    //TODO: implement
    return value_;
}
