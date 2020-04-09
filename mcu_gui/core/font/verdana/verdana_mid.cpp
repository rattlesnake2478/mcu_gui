#include "verdana_mid.h"
#include "verdana_mid_data.h"

using namespace McuGui;

VerdanaMidFont::VerdanaMidFont()
    :AbstractFontRenderer() {
    addRangeFontWriter(ASCII_FONT_START, ASCII_FONT_END, FontDataWriter(ASCII, {12, 13}, 0));
    addRangeFontWriter(RUS_FONT_START, RUS_FONT_END, FontDataWriter(RUS, {13, 16}, -2));
}
