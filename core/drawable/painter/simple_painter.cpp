#include "simple_painter.h"

#include <cmath>
#include <utility>
#include <algorithm>

using namespace mcugui;

void
SimplePainter::
drawPoint(Point p) {
  canvas_.plot(p, pen_);
}

void
SimplePainter::
setPen(Color c) {
  pen_ = c;
};

void
SimplePainter::
drawLine(Point start, Point end) {
  bool steep = false;
      if (std::abs(start.x-end.x) < std::abs(start.y-end.y)) {
          std::swap(start.x, start.y);
          std::swap(end.x, end.y);
          steep = true;
      }
      if (start.x > end.x) {
          std::swap(start.x, end.x);
          std::swap(start.y, end.y);
      }
      CoordType dx = end.x - start.x;
      CoordType dy = end.y - start.y;
      CoordType derror2 = std::abs(dy)*2;
      CoordType error2 = 0;
      CoordType y = start.y;
      for (CoordType x = start.x; x <= end.x; x++) {
          if (steep) {
              drawPoint({y, x});
          } else {
              drawPoint({x, y});
          }
          error2 += derror2;

          if (error2 > dx) {
              y += (end.y > start.y ? 1 : -1);
              error2 -= dx * 2;
          }
      }
}

void
SimplePainter::
drawTriangle(Point v1, Point v2, Point v3) {
  if (v1.y==v2.y && v1.y==v3.y) return;
      if (v1.y>v2.y) std::swap(v1, v2);
      if (v1.y>v3.y) std::swap(v1, v3);
      if (v2.y>v3.y) std::swap(v2, v3);

      CoordType total_height = v3.y-v1.y;
      for (CoordType i=0; i<total_height; i++) {
          bool second_half = i>v2.y-v1.y || v2.y==v1.y;
          CoordType segment_height = second_half ? v3.y-v2.y : v2.y-v1.y;
          float alpha = (float)i/total_height;
          float beta  = (float)(i-(second_half ? v2.y-v1.y : 0))/segment_height;
          Point A =               v1 + (v3-v1)*alpha;
          Point B = second_half ? v2 + (v3-v2)*beta : v1 + (v2-v1)*beta;
          if (A.x>B.x) std::swap(A, B);
          for (CoordType j=A.x; j<=B.x; j++) {
              drawPoint({j, (CoordType)(v1.y+i)});
          }
      }

}
