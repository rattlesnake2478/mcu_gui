#ifndef ARROW_H
#define ARROW_H

#include "../../core/drawable/rasterizable.h"
#include "../../core/drawable/primitives/primitives.h"

namespace mcugui {

class Arrow : public Rasterizable
{
public:
  Arrow(Point center, LenType width, LenType height, Color color);
  void moveAndRotate(LenType dist, float angle);

private:
  Point center_;
  LenType width_;
  LenType height_;
  Triangle triangle_;
};

} // end namespace mcugui



#endif // ARROW_H
