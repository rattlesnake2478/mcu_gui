#ifndef ABSTRACT_PRIMITIVE_H
#define ABSTRACT_PRIMITIVE_H

#include "../painter/painter_interface.h"

namespace mcugui {

struct AbstractPrimitive
{
public:
  AbstractPrimitive(Color c): c(c) {};
  virtual void rasterize(PainterInterface& painter) const = 0;
  Color c;
};

} // end namespace mcugui

#endif // ABSTRACT_PRIMITIVE_H
