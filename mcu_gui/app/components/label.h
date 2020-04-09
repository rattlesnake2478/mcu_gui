#ifndef LABEL_H
#define LABEL_H

#include "../../core/widget.h"
#include "../../core/font/font.h"

namespace McuGui {
    // please use Win1251 for correct view
    // TODO: add utf-8 support
    class Label: public AbstractWidget {
    public:
        explicit Label(std::string text, FontType type);
        virtual void paint(PainterInterface& painter) const override;
    protected:
        std::string text_;
        std::unique_ptr<AbstractFontRenderer> font_renderer_;
    };
} // end namespace McuGui

#endif // LABEL_H
