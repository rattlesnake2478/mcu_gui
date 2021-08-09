#ifndef PAINTER_INTERFACE_H
#define PAINTER_INTERFACE_H

#include "../../color.h"

namespace mcugui {

class PainterInterface {
public:
  virtual void setPen(Color c) = 0;
  virtual void drawPoint(Point p) = 0;
  virtual void drawLine(Point p1, Point p2) = 0;
  virtual void drawTriangle(Point p1, Point p2, Point p3) = 0;
};


} // end namespace mcugui

#endif // PAINTER_INTERFACE_H
