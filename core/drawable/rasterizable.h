#ifndef RASTERIZABLE_H
#define RASTERIZABLE_H

#include "drawable.h"
#include "primitives/abstract_primitive.h"

#include <vector>

namespace mcugui {

class Rasterizable : public Drawable
{
public:
  Rasterizable(Rect rect): Drawable(rect) {};
  virtual void draw(DriverInterface& driver) const override;

protected:
  void addPrimitive(AbstractPrimitive* primitive);
  virtual void rasterize(DriverInterface& driver) const;

private:
  std::vector<AbstractPrimitive*> primitives;

};

} // end namespace mcugui

#endif // RASTERIZABLE_H
