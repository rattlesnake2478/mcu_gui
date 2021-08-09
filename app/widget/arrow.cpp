#include "arrow.h"
#include "../../core/linear/matrix.h"

using namespace mcugui;

Arrow::Arrow(Point center, LenType width, LenType height, Color color):
  Rasterizable({
    (CoordType)(center.x - width / 2),
    center.y,
    width,
    height
  }),
  center_(center),
  width_(width),
  height_(height),
  triangle_({0, 0},
    {(CoordType)(width - 1), 0},
    {(CoordType)(width / 2 - 1), (CoordType)(height - 1)},
    color
  )
{
  addPrimitive(&triangle_);
}

void
Arrow::moveAndRotate(LenType dist, float angle) {

  // prepare matrixes
  auto vertexMatrix = FloatMatrix::fromVertexes({
    {(CoordType)(- width_ / 2), 0},
    {(CoordType)(width_ / 2), 0},
    {0, (CoordType)(height_)}
  });
  auto transformMatrix = TransformMatrix::move(0, (CoordType)dist) * TransformMatrix::rotate(angle);
  auto result = (vertexMatrix * transformMatrix).toVertexes();

  // update triangle data
  triangle_.p1 = result[0];
  triangle_.p2 = result[1];
  triangle_.p3 = result[2];
  rect_ = triangle_.getBoundRect();

  // convert triangle coords to canvas coords
  triangle_.p1 = triangle_.p1 - rect_.getOrigin();
  triangle_.p2 = triangle_.p2 - rect_.getOrigin();
  triangle_.p3 = triangle_.p3 - rect_.getOrigin();
  rect_.moveTo(center_ + rect_.getOrigin());

}
