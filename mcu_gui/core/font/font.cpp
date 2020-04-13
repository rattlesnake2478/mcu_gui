#include "font.h"
#include "verdana/verdana_mid.h"
#include "verdana/verdana_number_20.h"

using namespace McuGui;

FontDataWriter::FontDataWriter(const uint8_t* const data_ptr, Dimension size, int8_t align)
    :data_ptr_(data_ptr), size_(size), align_(align) {
    column_size_ = size.h % 8 > 0 ? size.h / 8 + 1 : size.h / 8;
}

CoordType
FontDataWriter::paintChar(uint8_t offset, PainterInterface& painter) const {
    auto ptr = data_ptr_ + offset * (size_.w * column_size_ + 1);
    auto char_width = *ptr;
    for (uint8_t j = 0; j < char_width; j++) {
        for(uint8_t i = 0; i < size_.h; i++) {
            auto data = ptr[j*column_size_ + i / 8 + 1];
            if (data & 1 << (i % 8)) painter.drawPoint({j, (CoordType)(i + align_)});
        }
    }
    return char_width;
}

void
AbstractFontRenderer::addRangeFontWriter(uint8_t start, uint8_t end, FontDataWriter writer) {
    range_font_writers_.push_back(std::make_tuple(start, end, writer));
}

CoordType
AbstractFontRenderer::renderChar(uint8_t ch, PainterInterface& painter) const {
    for(auto writer: range_font_writers_) {
        if (ch >= std::get<0>(writer) && ch <= std::get<1>(writer)) {
            return std::get<2>(writer).paintChar(ch - std::get<0>(writer), painter);
        }
    }
    return 0;
}

std::unique_ptr<AbstractFontRenderer>
AbstractFontRenderer::getFontByType(FontType type) {
    switch (type) {
    case VERDANA_NUMBER_20:
        return std::make_unique<VerdanaNumber20Font>();
    case VERDANA_MID:
    default:
        return std::make_unique<VerdanaMidFont>();
    }
}

