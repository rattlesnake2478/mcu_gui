#ifndef LAMPS_H
#define LAMPS_H

#include "../../core/primitives.h"

namespace McuGui {

    const Mask LEFT_TURN_GLYPH = {32,32,{0x78000,0x78000,0xf8000,0x1f8000,0x3f8000,0x7b8000,0xf38000,0x1e3ffff,0x3c3ffff,0x781ffff,0xf000007,0x1e000007,0x3c000007,0x78000007,0xf0000007,0xe0000007,0xe0000007,0xf0000007,0x78000007,0x3c000007,0x1e000007,0xf000007,0x781ffff,0x3c3ffff,0x1e3ffff,0xf38000,0x7b8000,0x3f8000,0x1f8000,0x1f8000,0xf8000,0x78000}};
    const Mask RIGHT_TURN_GLYPH = {32,32,{0x1e000,0x1e000,0x1f000,0x1f800,0x1fc00,0x1de00,0x1cf00,0xffffc780,0xffffc3c0,0xffff81e0,0xe00000f0,0xe0000078,0xe000003c,0xe000001e,0xe000000f,0xe0000007,0xe0000007,0xe000000f,0xe000001e,0xe000003c,0xe0000078,0xe00000f0,0xffff81e0,0xffffc3c0,0xffffc780,0x1cf00,0x1de00,0x1fc00,0x1f800,0x1f800,0x1f000,0x1e000}};
    const Mask BATTERY_GLYPH = {32,32,{0x0,0x0,0x0,0x0,0x0,0x7e007e0,0x7e007e0,0x7e007e0,0xffffffff,0xffffffff,0xc0000003,0xc0000003,0xc1800003,0xc1800003,0xc7e007e3,0xc7e007e3,0xc1800003,0xc1800003,0xc0000003,0xc0000003,0xc0000003,0xc0000003,0xc0000003,0xc0000003,0xffffffff,0xffffffff,0x0,0x0,0x0,0x0,0x0,0x0}};
    const Mask NEUTRAL_GLYPH = {32,32,{0x0,0x7f8003fc,0x7fc003fc,0x7fe003fc,0x7fe003fc,0x7ff003fc,0x7ff803fc,0x7ffc03fc,0x7ffc03fc,0x7ffe03fc,0x7fff03fc,0x7fff03fc,0x7fff83fc,0x7fffc3fc,0x7fffe3fc,0x7fbfe3fc,0x7f9ff3fc,0x7f8ffbfc,0x7f8ffffc,0x7f87fffc,0x7f83fffc,0x7f83fffc,0x7f81fffc,0x7f80fffc,0x7f807ffc,0x7f807ffc,0x7f803ffc,0x7f801ffc,0x7f801ffc,0x7f800ffc,0x7f8007fc,0x7f8003fc}};
    const Mask HIGH_BEAM_GLYPH = {32,32,{0xfc00,0xfe00,0x30780,0x303c0,0x300e0,0x30030,0xffe30038,0xffe3001c,0x3000e,0x30006,0x30006,0x30006,0x30007,0x30003,0x30003,0xffe30003,0xffe30003,0x30003,0x30003,0x30007,0x30006,0x30006,0x30006,0x3000e,0xffe3001c,0xffe30038,0x30030,0x300e0,0x303c0,0x30780,0xfe00,0xfc00}};
    const Mask GPS_GLYPH = {32,32,{0x0,0x180000,0x180000,0x180000,0x183800,0x183800,0x1ff800,0xc2000,0xe2000,0x72000,0x7a000,0x79e000,0x31ff00,0x123f00,0xc0000,0x60000,0x20000,0x0,0xfc7e1f0,0x1fe7f3f8,0x3ce77398,0x38077380,0x39e7f1f0,0x39e7e0f8,0x38e70038,0x3ce70338,0x1fe703f8,0xf8701f0,0x0,0x0,0x0,0x0}};
    const Mask TEMP_GLYPH = {32,32,{0x18000,0x18000,0x18000,0x1fc00,0x1fc00,0x1fc00,0x18000,0x18000,0x1fc00,0x1fc00,0x1fc00,0x18000,0x18000,0x1fc00,0x1fc00,0x1fc00,0x18000,0x18000,0x18000,0x7ff99ffe,0x18000,0x18000,0x3c000,0x7fcff3fe,0xff000,0x1ff800,0x1ff800,0x7fdffbfe,0x1ff800,0xff000,0xff000,0x3c000}};
}


#endif // LAMPS_H
