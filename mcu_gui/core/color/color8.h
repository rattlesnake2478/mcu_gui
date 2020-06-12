#ifndef COLOR8_H
#define COLOR8_H

#include <inttypes.h>

namespace McuGui {

typedef uint8_t Color;

const Color COLOR_RED = 35;
const Color COLOR_BLUE = 210;
const Color COLOR_GREEN = 185;
const Color COLOR_CYAN = 180;
const Color COLOR_MAGENTA = 30;
const Color COLOR_YELLOW = 5;

const Color COLOR_LIGHT_RED = 21;
const Color COLOR_LIGHT_BLUE = 126;
const Color COLOR_LIGHT_GREEN = 111;
const Color COLOR_LIGHT_CYAN = 108;
const Color COLOR_LIGHT_MAGENTA = 18;
const Color COLOR_LIGHT_YELLOW = 3;

const Color COLOR_DARK_RED = 143;
const Color COLOR_DARK_BLUE = 213;
const Color COLOR_DARK_GREEN = 203;
const Color COLOR_DARK_CYAN = 201;
const Color COLOR_DARK_MAGENTA = 141;
const Color COLOR_DARK_YELLOW = 131;

const Color COLOR_WHITE = 0;
const Color COLOR_LIGHT_GREY = 43;
const Color COLOR_GREY = 129;
const Color COLOR_DARK_GREY = 172;
const Color COLOR_BLACK = 255;
const Color COLOR_TRANSPARENT = 255;

const Color COLOR_BROWN = 100;
const Color COLOR_ORANGE = 17;

bool isTransparent(Color c);
Color mix(Color src, Color dst);
const uint32_t* getColorTable();

} // end namespace McuGui

#endif // COLOR8_H

