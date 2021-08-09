#ifndef DRIVERINTERFACE_H
#define DRIVERINTERFACE_H

#include "../color.h"
#include "../bitmap.h"

namespace mcugui {

class DriverInterface
{
public:
    virtual void fillRect(const Rect& rect, Color color) = 0;
    virtual void copyRect(const Rect& rect, const uint8_t *from) = 0;
    virtual void drawBitmap(Bitmap bitmap, Point pos) = 0;
};

} // end namespace mcugui

#endif // DRIVERINTERFACE_H
