#include "bitmap.h"

namespace mcugui {

std::vector<Bitmap::Data> Bitmap::storage = {};

Bitmap Bitmap::registerBitmapData(const Data data) {
    Bitmap::storage.push_back(data);
    return Bitmap(Bitmap::storage.size());
}

const uint8_t*
Bitmap::getData() const {
    return Bitmap::storage[id-1].data;
}

uint16_t
Bitmap::getWidth() const {
    return Bitmap::storage[id-1].width;
};

uint16_t Bitmap::getHeight() const {
    return Bitmap::storage[id-1].height;
};

PixelFormat
Bitmap::getFormat() const {
    return Bitmap::storage[id-1].format;
};


} // end namespace mcugui
