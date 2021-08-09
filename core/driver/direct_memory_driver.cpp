#include "direct_memory_driver.h"

using namespace mcugui;

template<typename T>
void
DirectMemoryDriver::
fillRegion(const Rect& rect, Color color){
  if (isOutside(rect)) return;
  const auto drawableRect = getDrawableRect(rect);
  const auto offset = calculateOffset({drawableRect.x, drawableRect.y});
  size_t gap = width_ - drawableRect.width;
  const auto colVal = color.getValue(pixelFormat_);
  T* start = (T*)dataPtr_ + offset;
  for(LenType y = 0; y < drawableRect.height; ++y) {
    for(LenType x = 0; x < drawableRect.width; ++x) {
      *start++ = (T)colVal;
    }
    start += gap;
  }
}

template<typename T, class Callback>
void
DirectMemoryDriver::
copyRegion(const Rect& rect, const uint8_t* src, Callback callback) {
  if (isOutside(rect)) return;
  const auto drawableRect = getDrawableRect(rect);
  const auto offset = calculateOffset({drawableRect.x, drawableRect.y});
  size_t gap = width_ - drawableRect.width;

  // work with bounds
  LenType rowStart = rect.y < 0 ? - rect.y : 0;
  LenType rowEnd = rect.bottom() >= height_ ? height_ - rect.y : rect.height;
  LenType colStart = rect.x < 0 ? - rect.x : 0;
  LenType colEnd = rect.right() >= width_ ? width_ - rect.x : rect.width;
  LenType colGap = rect.width + colStart - colEnd;
  size_t srcOffset = colStart + rowStart * rect.width;

  T* start = (T*)dataPtr_ + offset;
  T* source = (T*)src + srcOffset;
  for(LenType y = rowStart; y < rowEnd; ++y) {
    for(LenType x = colStart; x < colEnd; ++x) {
      callback(source, start);
      ++start;
      ++source;
    }
    start += gap;
    source += colGap;
  }
}

void
DirectMemoryDriver::
fillRect(const Rect& rect, Color color) {
  switch (pixelFormat_) {
  case ARGB32:
  case RGB24:
    fillRegion<uint32_t>(rect, color);
    break;
  case RGB555:
  case RGB565:
    fillRegion<uint16_t>(rect, color);
    break;
  case CLUT8:
    fillRegion<uint8_t>(rect, color);
 }

}

void
DirectMemoryDriver::
copyRect(const Rect& rect, const uint8_t *from) {
  switch (pixelFormat_) {
  case ARGB32:
      copyRegion<uint32_t>(rect, from, [](uint32_t* src, uint32_t* dst){
        // alpha composing
        float sa = (float)(uint8_t)(*src >> 24) / 0xFF;
        uint8_t sr = (uint8_t)(*src >> 16);
        uint8_t sg = (uint8_t)(*src >> 8);
        uint8_t sb = (uint8_t)*src;

        float da = (float)(uint8_t)(*dst >> 24) / 0xFF;
        uint8_t dr = (uint8_t)(*dst >> 16);
        uint8_t dg = (uint8_t)(*dst >> 8);
        uint8_t db = (uint8_t)*dst;

        *dst = ((uint32_t)((sa + da * (1 - sa)) * 0xFF) << 24)
             | ((uint32_t)(sr * sa + dr * (1 - sa)) << 16)
             | ((uint32_t)(sg * sa + dg * (1 - sa)) << 8)
             | ((uint32_t)(sb * sa + db * (1 - sa)) << 0);
      });
      break;
  case RGB24:
      copyRegion<uint32_t>(rect, from, [](uint32_t* src, uint32_t* dst){
        *dst = *src;
      });
      break;
  case RGB555:
  case RGB565:
      copyRegion<uint16_t>(rect, from, [](uint16_t* src, uint16_t* dst){
        *dst = *src;
      });
      break;
  case CLUT8:
      copyRegion<uint8_t>(rect, from, [](uint8_t* src, uint8_t* dst){
        *dst = *src;
      });
  }
}

void
DirectMemoryDriver::
drawBitmap(Bitmap bitmap, Point pos) {
  if (bitmap.getFormat() != pixelFormat_) {
      // TODO: log an error about incompatible formats
      return;
  }
  Rect rect = {pos.x, pos.y, bitmap.getWidth(), bitmap.getHeight()};
  copyRect(rect, bitmap.getData());
}

size_t
DirectMemoryDriver::
calculateOffset(Point pos) const {
    return (pos.x + pos.y * width_);
}

Rect
DirectMemoryDriver::
getDrawableRect(const Rect& rect) const {
  CoordType xLeft = rect.x < 0 ? 0 : rect.x;
  CoordType yTop = rect.y < 0 ? 0 : rect.y;
  CoordType xRight = rect.x + rect.width >= width_ ? width_  : rect.x + rect.width;
  CoordType yBottom = rect.y + rect.height >= height_ ? height_ : rect.y + rect.height;
  return {xLeft, yTop, (LenType)(xRight - xLeft), (LenType)(yBottom - yTop)};
}

bool
DirectMemoryDriver::
isOutside(const Rect& rect) const {
  Rect current = {0,0, width_, height_};
  return !current.intersect(rect);
}
