#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 320
#define HEIGHT 240

class ScreenBuffer {
    private:
    public:
        ScreenBuffer(uint16_t w, uint16_t h);
        ~ScreenBuffer();
        void drawBitmap(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t * bitmap, uint16_t transparent);
        void clear(uint16_t color);
        uint16_t * _buffer;
        uint16_t width, height;
        uint32_t length;
        uint16_t * buffer;
};
