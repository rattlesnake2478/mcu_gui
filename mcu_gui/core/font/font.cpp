#include "font.h"
#include "verdana.h"

using namespace McuGui;

AbstractFont::AbstractFont(
        const unsigned char* ascii,
        const unsigned char* rus,
        Dimension ascii_dim,
        Dimension rus_dim)
    : ascii_ptr_(ascii), rus_ptr_(rus), ascii_dim_(ascii_dim), rus_dim_(rus_dim){};


// Too complex. TODO: rework to separate writers with own dimensions and render logic
CoordType
AbstractFont::paintChar(const unsigned char& ch, PainterInterface& painter) const {
    if ( (ch < 32 || ch > 127) && (ch < 192 )) return 0; // char is out of font
    const uint8_t* base_ptr = (ch >= 192) ?  rus_ptr_ : ascii_ptr_;
    const Dimension& dim = (ch >= 192) ? rus_dim_ : ascii_dim_;
    const uint16_t offset = (ch >= 192)
            ? (ch - 192) * (rus_dim_.w * 2 + 1)
            : (ch - 32)  * (ascii_dim_.w * 2 + 1);  // two bytes for char. 2 is magic for all!
                                                    // but should be bytes of height
                                                    // mod 8. TODO: update for another fonts sizes
    auto data_ptr = base_ptr + offset;
    uint8_t width = data_ptr[0];
    auto height_align = (ch >= 192) ? 0 : rus_dim_.h - ascii_dim_.h;
    for (uint8_t j = 0; j < width; j++) {
        for(uint8_t i = 0; i < dim.h; i++) {
            auto data = data_ptr[j*2 + i / 8 + 1];
            if (data & 1 << (i % 8)) painter.drawPoint({j, (CoordType)(i + height_align)}); // kind of magic
        }
    }
    return width + GAP;

}

VerdanaMidFont::VerdanaMidFont()
    :AbstractFont(VERDANA_ASCII_MID, VERDANA_RUS_MID, {12, 13}, {13,16}) {};

VerdanaMidBoldFont::VerdanaMidBoldFont()
    :AbstractFont(VERDANA_ASCII_MID_BOLD, VERDANA_RUS_MID_BOLD, {16, 14}, {14,15}) {};


std::shared_ptr<AbstractFont> buildFontByType(FontType type) {
    switch (type) {
    case VERDANA_MID_BOLD:
        return std::make_shared<VerdanaMidBoldFont>();
    case VERDANA_MID:
    default:
        return std::make_shared<VerdanaMidFont>();
    }
}

Label::Label(std::string text, FontType type): text_(text) {
    font_ = buildFontByType(type);
};

void
Label::paint(PainterInterface& painter) const {
    CoordType offset = 0;
    for(const unsigned char& ch : text_) {
        MovedPainter p(painter, offset, 0);
        offset += font_->paintChar(ch, p);
    }
};
