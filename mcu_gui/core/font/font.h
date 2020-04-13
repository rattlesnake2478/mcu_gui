#ifndef FONT_H
#define FONT_H

#include "../painter.h"
#include <tuple>
#include <memory>

namespace McuGui {

enum FontType {
    VERDANA_MID = 0,
    VERDANA_NUMBER_20,
};

const uint8_t ASCII_FONT_START = 32;
const uint8_t ASCII_FONT_END = 127;
const uint8_t RUS_FONT_START = 192;
const uint8_t RUS_FONT_END = 255;
const uint8_t NUMBER_FONT_START = 45;
const uint8_t NUMBER_FONT_END = 57;

// TODO: think about linking. If we dont use the font - it should not be linked
class FontDataWriter {
public:
    FontDataWriter(const uint8_t* const data_ptr, Dimension size, int8_t align = 0);
    CoordType paintChar(uint8_t offset, PainterInterface& painter) const;
    Dimension getCharSize(uint8_t offset) const;
protected:
    const uint8_t* const data_ptr_;
    const Dimension size_;
    int8_t align_;
    uint8_t column_size_;
};

class AbstractFontRenderer {
public:
    CoordType renderChar(uint8_t ch, PainterInterface& painter) const;
    Dimension getCharSize(uint8_t ch) const;
    static std::unique_ptr<AbstractFontRenderer> getFontByType(FontType);
protected:
    typedef std::tuple<uint8_t, uint8_t, FontDataWriter> RangeFontWriter;
    void addRangeFontWriter(uint8_t start, uint8_t end, FontDataWriter writer);
    AbstractFontRenderer() {};
    std::vector<RangeFontWriter> range_font_writers_;
};

} // end namespace McuGui
#endif // FONT_H
