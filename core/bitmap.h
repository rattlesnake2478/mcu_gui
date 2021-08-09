#ifndef BITMAP_H
#define BITMAP_H

#include "types.h"

#include <vector>

namespace mcugui {

class Bitmap
{
public:

    using Id = uint16_t;

    struct Data {
        const uint8_t* const data;
        const LenType width;
        const LenType height;
        const PixelFormat format;
    };

    const uint8_t* getData() const;
    LenType getWidth() const;
    LenType getHeight() const;
    PixelFormat getFormat() const;

    static Bitmap registerBitmapData(const Data data);

private:
    explicit Bitmap(Id idVal): id(idVal) {};

    Id id;
    static std::vector<Data> storage;

};

} // end namespace mcugui
#endif // BITMAP_H
