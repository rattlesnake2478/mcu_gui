#ifndef COLOR_TEMPLATE_H
#define COLOR_TEMPLATE_H

#include <array>

namespace McuGui {

enum class Color {
    RED,
    BLUE,
    GREEN,
    CYAN,
    MAGENTA,
    YELLOW,
    BROWN,
    ORANGE,
    WHITE,
    GREY,
    BLACK,
    TRANSPARENT,
    LIGHT_RED,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_MAGENTA,
    LIGHT_YELLOW,
    LIGHT_GREY,
    DARK_RED,
    DARK_BLUE,
    DARK_GREEN,
    DARK_CYAN,
    DARK_MAGENTA,
    DARK_YELLOW,
    DARK_GREY,
};

template <typename T, typename Derived> class ColorFormatTemplate {
protected:
    using ColorTable = std::array<T, 26>;

public:
    using data_type = T;
    static T fromConstant(Color c) { return Derived::clut_[static_cast<size_t>(c)]; };
    static bool isTransparent(T c) { return Derived::clut_[static_cast<size_t>(Color::TRANSPARENT)] == c; };
    static T mix(T src, T) { return src; };
};

class ColorCLUT8Mac: public ColorFormatTemplate<uint8_t, ColorCLUT8Mac> {
public:
    static ColorTable const clut_;
    using data_type = ColorFormatTemplate::data_type;
};

class ColorARGB32: public ColorFormatTemplate<uint32_t, ColorARGB32> {
public:
    static ColorTable const clut_;
    using data_type = ColorFormatTemplate::data_type;
    static uint32_t mix(uint32_t src, uint32_t dst);
};

} // end namespace McuGui

#endif // COLOR_TEMPLATE_H
