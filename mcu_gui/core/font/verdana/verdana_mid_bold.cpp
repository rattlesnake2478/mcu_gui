#include "verdana_mid_bold.h"
#include "verdana_mid_bold_data.h"

using namespace McuGui;

VerdanaMidBoldFont::VerdanaMidBoldFont()
    :AbstractFontRenderer() {
    addRangeFontWriter(ASCII_FONT_START, ASCII_FONT_END, FontDataWriter(ASCII, {16, 14}, 0));
    addRangeFontWriter(RUS_FONT_START, RUS_FONT_END, FontDataWriter(RUS, {14, 15}, -1));
}
