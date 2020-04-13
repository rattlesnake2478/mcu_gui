#include "color32.h"

bool McuGui::isTransparent(Color c) {
   return (c & 0xFF000000) == 0xFF000000;
}
