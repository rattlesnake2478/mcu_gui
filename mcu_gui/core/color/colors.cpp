#include "colors.h"

using namespace McuGui;

ColorCLUT8Mac::ColorTable const ColorCLUT8Mac::clut_ = {
    35,
    210,
    185,
    180,
    30,
    5,
    100,
    17,
    0,
    129,
    255,
    245,
    21,
    126,
    111,
    108,
    18,
    3,
    43,
    143,
    213,
    203,
    201,
    141,
    131,
    172,
};

ColorARGB32::ColorTable const ColorARGB32::clut_ = {
    0xFFFF0000,
    0xFF0000FF,
    0xFF00FF00,
    0xFF00FFFF,
    0xFFFF00FF,
    0xFFFFFF00,
    0xFFA52A2A,
    0xFFFFA500,
    0xFFFFFFFF,
    0xFF808080,
    0xFF000000,
    0x00FFFFFF,
    0xFFFF8080,
    0xFF8080FF,
    0xFF80FF80,
    0xFF80FFFF,
    0xFFFF80FF,
    0xFFFFFF80,
    0xFFD3D3D3,
    0xFF800000,
    0xFF000080,
    0xFF008000,
    0xFF008080,
    0xFF800080,
    0xFF808000,
    0xFF404040,
};

uint32_t ColorARGB32::mix(uint32_t src, uint32_t dst) {
    // alpha compositing is here
   float sa = (float)(uint8_t)(src >> 24) / 0xFF;
   uint8_t sr = (uint8_t)(src >> 16);
   uint8_t sg = (uint8_t)(src >> 8);
   uint8_t sb = (uint8_t)src;

   uint8_t dr = (uint8_t)(dst >> 16);
   uint8_t dg = (uint8_t)(dst >> 8);
   uint8_t db = (uint8_t)dst;

   return ((uint32_t)0xFF << 24)
        | ((uint32_t)(sr * sa + dr * (1 - sa)) << 16)
        | ((uint32_t)(sg * sa + dg * (1 - sa)) << 8)
        | ((uint32_t)(sb * sa + db * (1 - sa)) << 0);
}
