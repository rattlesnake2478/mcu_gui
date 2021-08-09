#ifndef COLOR_H
#define COLOR_H

#include "types.h"

namespace mcugui {

class Color {
public:

  Color(uint32_t value): value_(value){};
  uint32_t getValue(PixelFormat format = PixelFormat::ARGB32);

  static Color getDefault() { return 0x0; }

protected:
  uint8_t getAlpha() const;
  uint8_t getRed() const;
  uint8_t getGreen() const;
  uint8_t getBlue() const;

  uint32_t convertToRgb24() const;
  uint32_t convertToRgb565() const;
  uint32_t convertToRgb555() const;
  uint32_t convertToClut8() const;
  uint32_t value_;
};

} // end namespace mcugui
#endif // COLOR_H
