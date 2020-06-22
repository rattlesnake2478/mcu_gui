#ifndef DIGITSEGMENT_H
#define DIGITSEGMENT_H

#include "../core/widget.h"

namespace McuGui {

class DigitSegment: public AbstractWidget {
public:
    enum Type {
        Horizontal = 0,
        Vertical,
    };
    enum Size {
        Small = 0,
        Mid,
        Huge
    };

    static Dimension getSize(Size size) {
        switch (size) {
        case Small:
            return {6, 18};
        case Mid:
            return {10, 30};
        case Huge:
        default:
            return {16, 54};
        }
    }

    DigitSegment(Type type, Size size = Size::Mid, Color color = COLOR_RED, Color border = COLOR_WHITE):
        type_(type), color_(color), border_(border), size_(size) { };

    virtual void paint(PainterInterface& painter) const override;

protected:
    Type type_;
    Color color_;
    Color border_;
    Size size_;
};

} // end namespace McuGui

#endif // DIGITSEGMENT_H
