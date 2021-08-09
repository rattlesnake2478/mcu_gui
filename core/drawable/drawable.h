#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../driver/driver_interface.h"

namespace mcugui {

class Drawable
{
public:
  Drawable(Rect rect): rect_(rect) {};
  virtual void draw(DriverInterface& driver) const = 0;

protected:
  Rect rect_;
};

} // end namespace mcugui

#endif // DRAWABLE_H
