#include "matrix.h"
#include <math.h>

using namespace McuGui;

const float DEG2RAD = 0.0174533;

TransformMatrix
TransformMatrix::move(CoordType x, CoordType y) {
    return TransformMatrix({1,0,0,
                            0,1,0,
                            (float)x,(float)y,1});
}

TransformMatrix
TransformMatrix::rotate(float angle) {
    float cosA = std::cos(angle * DEG2RAD) ;
    float sinA = std::sin(angle * DEG2RAD) ;
    return TransformMatrix({cosA,-sinA,0,
                            sinA,cosA,0,
                            0,0,1});
}
