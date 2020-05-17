#include "ScreenBuffer.h"

#include <Arduino.h>
#include <M5Stack.h>

ScreenBuffer::ScreenBuffer(uint16_t w, uint16_t h) {
    width = w;
    height = h;
    length = w * h;

    _buffer = (uint16_t *)heap_caps_malloc(sizeof(uint16_t) * length, MALLOC_CAP_SPIRAM);
    buffer = _buffer;
}

ScreenBuffer::~ScreenBuffer() {
    heap_caps_free(_buffer);
}


void ScreenBuffer::clear(uint16_t color)
{
    for (int i = 0; i < length; i++) _buffer[i] = color;
}

void ScreenBuffer::drawBitmap(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *bitmap, uint16_t transparent)
{
    Serial.println(h);
    int16_t over_height = y + h - height;
    Serial.println(over_height);
    if (over_height > 0)
        h -= over_height;
    Serial.println(h);

    int16_t over_width = x + w - width;
    int16_t copy_width = over_width > 0 ? w - over_width : w;

    if (copy_width <= 0 || h <= 0)
        return;

    uint16_t * dst = _buffer;
    uint16_t * src = (uint16_t *)bitmap;
    dst += width * y + x;

    for (int i = 0; i < h; i++)
    {
        memcpy(dst, src, 2 * copy_width);
        dst += width;
        src += w;
    }
}
