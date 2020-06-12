#ifndef COLOR32_H
#define COLOR32_H

#include <inttypes.h>

namespace McuGui {

typedef uint32_t Color;

const Color COLOR_RED = 0xFFFF0000;
const Color COLOR_BLUE = 0xFF0000FF;
const Color COLOR_GREEN = 0xFF00FF00;
const Color COLOR_CYAN = 0xFF00FFFF;
const Color COLOR_MAGENTA = 0xFFFF00FF;
const Color COLOR_YELLOW = 0xFFFFFF00;

const Color COLOR_LIGHT_RED = 0xFFFF8080;
const Color COLOR_LIGHT_BLUE = 0xFF8080FF;
const Color COLOR_LIGHT_GREEN = 0xFF80FF80;
const Color COLOR_LIGHT_CYAN = 0xFF80FFFF;
const Color COLOR_LIGHT_MAGENTA = 0xFFFF80FF;
const Color COLOR_LIGHT_YELLOW = 0xFFFFFF80;

const Color COLOR_DARK_RED = 0xFF800000;
const Color COLOR_DARK_BLUE = 0xFF000080;
const Color COLOR_DARK_GREEN = 0xFF008000;
const Color COLOR_DARK_CYAN = 0xFF008080;
const Color COLOR_DARK_MAGENTA = 0xFF800080;
const Color COLOR_DARK_YELLOW = 0xFF808000;

const Color COLOR_WHITE = 0xFFFFFFFF;
const Color COLOR_LIGHT_GREY = 0xFFD3D3D3;
const Color COLOR_GREY = 0xFF808080;
const Color COLOR_DARK_GREY = 0xFF404040;
const Color COLOR_BLACK = 0xFF000000;
const Color COLOR_TRANSPARENT = 0x00FFFFFF;

const Color COLOR_BROWN = 0xFFA52A2A;
const Color COLOR_ORANGE = 0xFFFFA500;

bool isTransparent(Color c);
Color mix(Color src, Color dst);

} // end namespace McuGui

#endif // COLOR32_H
