#ifndef LABEL_H
#define LABEL_H

#include "../core/widget.h"
#include "../core/font/font.h"

namespace McuGui {

enum TextAlign {
    ALIGN_LEFT = 0,
    ALIGN_RIGHT,
};

// please use Win1251 for correct view
// TODO: add utf-8 support
template<typename T> class AbstractLabel: public AbstractWidget {
public:
    AbstractLabel(T val, FontType type, TextAlign align = ALIGN_LEFT): val_(val), align_(align) {
        font_renderer_ = AbstractFontRenderer::getFontByType(type);
    }
    virtual void paint(PainterInterface& painter) const override {
        MovedPainter p(painter, 0, 0);
        switch (align_) {
        case ALIGN_LEFT:
            for(const unsigned char& ch : getStringData()) {
                p.move(font_renderer_->renderChar(ch, p), 0);
            }
            break;
        case ALIGN_RIGHT:
            auto data = getStringData();
            auto begin = data.crbegin();
            auto end = data.crend();
            for(auto it = begin; it != end; ++it) {
                auto char_size = font_renderer_->getCharSize(*it);
                p.move(-char_size.w, 0);
                font_renderer_->renderChar(*it, p);
            }
        }
    };
    void setValue(T val) { val_ = val; }
protected:
    virtual std::string getStringData() const = 0;
    T val_;
    std::unique_ptr<AbstractFontRenderer> font_renderer_;
    const TextAlign align_;
};

class TextLabel: public AbstractLabel<std::string> {
public:
    using AbstractLabel::AbstractLabel;
protected:
    std::string getStringData() const override { return val_; };
};

class NumberLabel: public AbstractLabel<float> {
public:
    NumberLabel(float val, FontType type, TextAlign align = ALIGN_LEFT, bool float_mode = true);
protected:
    bool float_mode_;
    std::string getStringData() const override;
};

} // end namespace McuGui

#endif // LABEL_H
