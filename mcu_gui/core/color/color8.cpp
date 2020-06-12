#include "color8.h"
#include "mac_os_palette.h"

const uint32_t* McuGui::getColorTable() {
    return macOsPalette;
}

bool McuGui::isTransparent(Color c) {
   return c == COLOR_TRANSPARENT;
}

McuGui::Color McuGui::mix(McuGui::Color src, McuGui::Color) {
    return src; // no alpha composing
}
