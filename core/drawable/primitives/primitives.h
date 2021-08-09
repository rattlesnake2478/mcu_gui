#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "abstract_primitive.h"

namespace mcugui {

struct Line: public AbstractPrimitive
{
  Line(Point p1, Point p2, Color c): AbstractPrimitive(c), p1(p1), p2(p2) {};
  void rasterize(PainterInterface& painter) const override { painter.drawLine(p1, p2); };

  Point p1;
  Point p2;
};

struct Triangle: public AbstractPrimitive
{
  Triangle(Point p1, Point p2, Point p3, Color c): AbstractPrimitive(c), p1(p1), p2(p2), p3(p3) {};
  void rasterize(PainterInterface& painter) const override { painter.drawTriangle(p1, p2, p3); };

  Point p1;
  Point p2;
  Point p3;

  CoordType getTop() {
    auto top = p1.y;
    if (p2.y < top) top = p2.y;
    if (p3.y < top) top = p3.y;
    return top;
  }

  CoordType getBottom() {
    auto bottom = p1.y;
    if (p2.y > bottom) bottom = p2.y;
    if (p3.y > bottom) bottom = p3.y;
    return bottom;
  }

  CoordType getLeft() {
    auto left = p1.x;
    if (p2.x < left) left = p2.x;
    if (p3.x < left) left = p3.x;
    return left;
  }

  CoordType getRight() {
    auto right = p1.x;
    if (p2.x > right) right = p2.x;
    if (p3.x > right) right = p3.x;
    return right;
  }

  Rect getBoundRect() {
    return Rect({
      getLeft(),
      getTop(),
      (LenType)(getRight() - getLeft()),
      (LenType)(getBottom() - getTop())
    });
  }
};

} // end namespace mcugui

#endif // PRIMITIVES_H
