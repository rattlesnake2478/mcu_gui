#include "canvas.h"

using namespace mcugui;

Canvas::Canvas(Rect rect, Color bg, PixelFormat format) :
rect_(rect), bg_(bg), format_(format)
{
  switch (format_) {
    case PixelFormat::CLUT8:
      initRegion<uint8_t>();
      fillRegion<uint8_t>();
      break;
    case PixelFormat::RGB565:
    case PixelFormat::RGB555:
      initRegion<uint16_t>();
      fillRegion<uint16_t>();
      break;
    case PixelFormat::RGB24:
    case PixelFormat::ARGB32:
    default:
      initRegion<uint32_t>();
      fillRegion<uint32_t>();
  }
}

Canvas::~Canvas() {
  delete[] memory_;
}

void
Canvas::plot(Point p, Color c) {
  if ((p.x >= rect_.width) || (p.y >= rect_.height)) return;
  switch (format_) {
    case PixelFormat::CLUT8:
      plotPoint<uint8_t>(p, c);
      break;
    case PixelFormat::RGB565:
    case PixelFormat::RGB555:
      plotPoint<uint16_t>(p, c);
      break;
    case PixelFormat::RGB24:
    case PixelFormat::ARGB32:
    default:
      plotPoint<uint32_t>(p, c);
  }
}

template<typename T>
void
Canvas::
initRegion() {
  T* region = new T[rect_.width * rect_.height];
  memory_ = (uint8_t*)region;
}


template<typename T>
void
Canvas::
fillRegion() {
  // TODO: optimize for full register copying
  // TODO: or use driver to speedup fill
  T value = (T)bg_.getValue(format_);
  T* ptr = (T*) memory_;
  for (LenType x = 0; x < rect_.width; ++x)
    for (LenType y = 0; y < rect_.height; ++y)
      *(ptr++) = value;
}

template<typename T>
void
Canvas::
plotPoint(Point p, Color c) {
  size_t offset = p.x + p.y * rect_.width;
  T* target = (T*) memory_ + offset;
  *target = (T)c.getValue(format_);
}
