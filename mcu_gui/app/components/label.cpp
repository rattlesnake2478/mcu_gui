#include "label.h"

using namespace McuGui;

Label::Label(std::string text, FontType type): text_(text) {
    font_renderer_ = AbstractFontRenderer::getFontByType(type);
};

void
Label::paint(PainterInterface& painter) const {
    CoordType offset = 0;
    for(const unsigned char& ch : text_) {
        MovedPainter p(painter, offset, 0);
        offset += font_renderer_->renderChar(ch, p);
    }
};
