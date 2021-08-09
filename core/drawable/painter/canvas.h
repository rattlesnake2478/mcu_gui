#ifndef CANVAS_H
#define CANVAS_H

#include "../../color.h"

namespace mcugui {

class Canvas {
public:
  Canvas(Rect rect, Color bg = Color::getDefault(), PixelFormat format = PixelFormat::ARGB32);
  virtual ~Canvas();
  void plot(Point p, Color c);
  uint8_t* getBuffer() const { return memory_; }
  Rect getRect() const { return rect_; }

private:
  template<typename T> void initRegion();
  template<typename T> void fillRegion();
  template<typename T> void plotPoint(Point p, Color c);
  Rect rect_;
  Color bg_;
  PixelFormat format_;
  uint8_t* memory_;
};

} // end namespace mcugui

#endif // CANVAS_H
