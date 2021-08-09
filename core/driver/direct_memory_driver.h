#ifndef DIRECTMEMORYDRIVER_H
#define DIRECTMEMORYDRIVER_H

#include "driver_interface.h"

namespace mcugui {

class DirectMemoryDriver: public DriverInterface
{
public:
    DirectMemoryDriver(uint8_t* ptr, LenType width, LenType height, PixelFormat pixelFormat = PixelFormat::ARGB32):
        dataPtr_(ptr),
        width_(width),
        height_(height),
        pixelFormat_(pixelFormat) {};
    virtual void fillRect(const Rect& rect, Color color) override;
    virtual void copyRect(const Rect& rect, const uint8_t* from) override;
    virtual void drawBitmap(Bitmap bitmap, Point pos) override;

protected:
    size_t calculateOffset(Point pos) const;
    Rect getDrawableRect(const Rect& rect) const;
    bool isOutside(const Rect& rect) const;
    template<typename T> void fillRegion(const Rect& rect, Color color);
    template<typename T, class Callback> void copyRegion(const Rect& rect, const uint8_t* src, Callback callback);
    uint8_t* dataPtr_;
    LenType width_;
    LenType height_;
    const PixelFormat pixelFormat_;



};

} // end namespace mcugui

#endif // DIRECTMEMORYDRIVER_H
