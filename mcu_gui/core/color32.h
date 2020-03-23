#ifndef COLOR32_H
#define COLOR32_H

#include <inttypes.h>

namespace McuGui {

typedef uint32_t Color;

const Color COLOR_RED = 0xFFFF0000;
const Color COLOR_BLUE = 0xFF0000FF;
const Color COLOR_GREEN = 0xFF00FF00;
const Color COLOR_YELLOW = 0xFFFFFF00;
const Color COLOR_WHITE = 0xFFFFFFFF;
const Color COLOR_BLACK = 0xFF000000;
const Color COLOR_GREY = 0xFF808080;
const Color COLOR_TRANSPARENT = 0x00000000;

} // end namespace McuGui

#endif // COLOR32_H
