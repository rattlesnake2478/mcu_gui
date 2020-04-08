#include "font.h"
#include "monotype_8x8.h"
#include "monotype_16x16.h"

using namespace McuGui;

CoordType
MonotypeTinyFont::paintChar(const char& ch, PainterInterface& painter) const {
    const size_t offset = ch * 8;
    for(uint8_t row = 0; row < 8; ++row) {
        auto data = MONOTYPE_TINY[offset + row];
        for (uint8_t col = 0; col < 8; ++col) {
            if (data & 1 << (7 - col)) painter.drawPoint({col, row});
        }
    }
    return (CoordType)8;
};

CoordType
MonotypeMidFont::paintChar(const char& ch, PainterInterface& painter) const {
    const size_t offset = ch * 16;
    for(uint8_t row = 0; row < 16; ++row) {
        auto data = MONOTYPE_MID[offset + row];
        for (uint8_t col = 0; col < 16; ++col) {
            if (data & 1 << (15 - col)) painter.drawPoint({col, row});
        }
    }
    return (CoordType)16;
};

std::shared_ptr<FontInterface> buildFontByType(FontType type) {
    switch (type) {
    case MONOTYPE_MID_FONT:
        return std::make_shared<MonotypeMidFont>();
    default:
        return std::make_shared<MonotypeTinyFont>();
    }
}

Label::Label(std::string text, FontType type): text_(text) {
    font_ = buildFontByType(type);
};

void
Label::paint(PainterInterface& painter) const {
    CoordType offset = 0;
    for(const char& ch : text_) {
        MovedPainter p(painter, offset, 0);
        offset += font_->paintChar(ch, p);
    }
};
