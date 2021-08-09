#ifndef SIMPLEPAINTER_H
#define SIMPLEPAINTER_H

#include "painter_interface.h"
#include "canvas.h"

namespace mcugui {

class SimplePainter : public PainterInterface {
public:
  SimplePainter(Canvas& canvas): canvas_(canvas), pen_(Color::getDefault()) {};
  virtual void setPen(Color c) override;
  virtual void drawPoint(Point p) override;
  virtual void drawLine(Point p1, Point p2) override;
  virtual void drawTriangle(Point p1, Point p2, Point p3) override;

private:
  Canvas& canvas_;
  Color pen_;
};


} // end namespace mcugui

#endif // SIMPLEPAINTER_H
