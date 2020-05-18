#include <M5Stack.h>
#include <Battery.h>
#include <Resources.h>
#include <ScreenBuffer.h>

Battery battery;
ScreenBuffer * screen;

const uint16_t *yukari_right[] = {
	Resources::yukari_run_right_0,
	Resources::yukari_run_right_0,
	Resources::yukari_run_right_0,
	Resources::yukari_run_right_1,
	Resources::yukari_run_right_1,
	Resources::yukari_run_right_1,
	Resources::yukari_run_right_2,
	Resources::yukari_run_right_2,
	Resources::yukari_run_right_2,
	Resources::yukari_run_right_3,
	Resources::yukari_run_right_3,
	Resources::yukari_run_right_3,
	Resources::yukari_run_right_4,
	Resources::yukari_run_right_4,
	Resources::yukari_run_right_4,
	Resources::yukari_run_right_5,
	Resources::yukari_run_right_5,
	Resources::yukari_run_right_5,
};

const uint16_t *maki_right[] = {
	Resources::maki_run_right_0,
	Resources::maki_run_right_0,
	Resources::maki_run_right_1,
	Resources::maki_run_right_1,
	Resources::maki_run_right_2,
	Resources::maki_run_right_2,
	Resources::maki_run_right_3,
	Resources::maki_run_right_3,
	Resources::maki_run_right_4,
	Resources::maki_run_right_4,
	Resources::maki_run_right_5,
	Resources::maki_run_right_5,
};

uint16_t yukari_index = 0, maki_index = 0;
unsigned long next_frame;

void setup()
{
	M5.begin(true, false, false, true);
	Serial.begin(76800);

	next_frame = 0;

	screen = new ScreenBuffer(320, 240);

	dacWrite(25, 0);
}

void loop()
{
	unsigned long time = micros();
	if (time < next_frame)
		delayMicroseconds(next_frame - time);
		
	screen->clear(0x0000);

	screen->drawBitmap(10, 20, 144, 192, yukari_right[yukari_index], 0x0000); // transparent for black
	if (++yukari_index >= 18) yukari_index = 0;
	
	screen->drawBitmap(160, 20, 160, 192, maki_right[maki_index], 0x0000); // transparent for black
	if (++maki_index >= 12) maki_index = 0;

	screen->drawBitmap(320 - battery.width, 0, battery.width, battery.height, battery.getBatteryLevelBitmap(), 0xf00f);
	
	M5.Lcd.drawBitmap(0, 0, 320, 240, screen->buffer);
	
	time = micros();
	while (time > next_frame)
		next_frame += 33333;

	M5.update(); // ボタン動作をチェックする関数っぽい
}
