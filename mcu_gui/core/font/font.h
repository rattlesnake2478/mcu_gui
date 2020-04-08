#ifndef FONT_H
#define FONT_H

#include "../widget.h"
#include <string>
#include <memory>

namespace McuGui {

class FontInterface {
public:

};

enum FontType {
    VERDANA_MID = 0,
    VERDANA_MID_BOLD,
};

class AbstractFont {
public:
    CoordType paintChar(const unsigned char& ch, PainterInterface& painter) const;

protected:
    const uint8_t GAP = 1; // points between chars

    AbstractFont(
            const unsigned char* ascii,
            const unsigned char* rus,
            Dimension ascii_dim,
            Dimension rus_dim);
    const unsigned char *ascii_ptr_;
    const unsigned char *rus_ptr_;
    Dimension ascii_dim_;
    Dimension rus_dim_;
};

class VerdanaMidFont: public AbstractFont {
public:
    VerdanaMidFont();
};

class VerdanaMidBoldFont: public AbstractFont {
public:
    VerdanaMidBoldFont();
};

// please use Win1251 for correct view
class Label: public AbstractWidget {
public:
    explicit Label(std::string text, FontType type);
    virtual void paint(PainterInterface& painter) const override;
protected:
    std::string text_;
    std::shared_ptr<AbstractFont> font_;
};

} // end namespace McuGui
#endif // FONT_H
