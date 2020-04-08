#ifndef FONT_H
#define FONT_H

#include "../widget.h"
#include <string>
#include <memory>

namespace McuGui {

enum FontType {
    MONOTYPE_TINY_FONT = 0,
    MONOTYPE_MID_FONT,
};

class FontInterface {
public:
    virtual CoordType paintChar(const char& ch, PainterInterface& painter) const = 0;
};

class MonotypeTinyFont: public FontInterface {
public:
    virtual CoordType paintChar(const char& ch, PainterInterface& painter) const override;
};

class MonotypeMidFont: public FontInterface {
public:
    virtual CoordType paintChar(const char& ch, PainterInterface& painter) const override;
};

class Label: public AbstractWidget {
public:
    explicit Label(std::string text, FontType type);
    virtual void paint(PainterInterface& painter) const override;
protected:
    std::string text_;
    std::shared_ptr<FontInterface> font_;

};



} // end namespace McuGui
#endif // FONT_H
