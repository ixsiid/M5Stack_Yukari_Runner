#include "Battery.h"

uint8_t Battery::getBatteryLevel()
{
    Wire.beginTransmission(0x75);
    Wire.write(0x78);
    Wire.endTransmission(false);
    if (Wire.requestFrom(0x75, 1))
    {
        return Wire.read();
        // 0xf0x0000 : empty
        // 0xe0x0000 : 25%
        // 0xc0x0000 : 50x0000%
        // 0x80x0000 : 75%
        // 0x0x00000x0000 : full
    }

    return 0xff;
}

uint8_t Battery::drawBatteryLevel()
{
    uint8_t level = this->getBatteryLevel();
    uint16_t *bmp;
    switch (level)
    {
    case 0x00:
        bmp = _full;
        break;
    case 0x80:
        bmp = _75;
        break;
    case 0xc0:
        bmp = _50;
        break;
    case 0xe0:
        bmp = _25;
        break;
    case 0xf0:
        bmp = _empty;
        break;
    default:
        bmp = _error;
        break;
    }
    M5.Lcd.drawBitmap(320 - 18, 0, 18, 9, bmp);
    return level;
}
