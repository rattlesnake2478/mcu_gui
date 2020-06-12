#include "color32.h"

bool McuGui::isTransparent(Color c) {
   return (c & 0xFF000000) == 0x0;
}

McuGui::Color McuGui::mix(McuGui::Color src, McuGui::Color dst) {
    // alpha compositing is here
    float sa = (float)(uint8_t)(src >> 24) / 0xFF;
    uint8_t sr = (uint8_t)(src >> 16);
    uint8_t sg = (uint8_t)(src >> 8);
    uint8_t sb = (uint8_t)src;

    uint8_t dr = (uint8_t)(dst >> 16);
    uint8_t dg = (uint8_t)(dst >> 8);
    uint8_t db = (uint8_t)dst;

    return ((Color)0xFF << 24)
         | ((Color)(sr * sa + dr * (1 - sa)) << 16)
         | ((Color)(sg * sa + dg * (1 - sa)) << 8)
         | ((Color)(sb * sa + db * (1 - sa)) << 0);
}
