#include "verdana_number_20.h"
#include "verdana_number_20_data.h"

using namespace McuGui;

VerdanaNumber20Font::VerdanaNumber20Font()
    :AbstractFontRenderer() {
    addRangeFontWriter(NUMBER_FONT_START, NUMBER_FONT_END, FontDataWriter(NUMBERS, {15, 20}, 0));
}

