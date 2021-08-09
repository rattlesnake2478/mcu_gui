#include "rasterizable.h"
#include "painter/simple_painter.h"

using namespace mcugui;

void
Rasterizable::
draw(DriverInterface& driver) const {
  rasterize(driver);
};

void
Rasterizable::
addPrimitive(AbstractPrimitive* primitive) {
  primitives.push_back(primitive);
};

void
Rasterizable::
rasterize(DriverInterface& driver) const {
  Canvas canvas(rect_);
  SimplePainter painter(canvas);

  for (const auto& primitive: primitives) {
    painter.setPen(primitive->c);
    primitive->rasterize(painter);
  }

  driver.copyRect(canvas.getRect(), canvas.getBuffer());
}
