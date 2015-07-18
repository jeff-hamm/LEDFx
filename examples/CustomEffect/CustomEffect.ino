#define LEDLIB_GRB_ORDER
#include <LEDFx.h>
#include <FastSPI_LED2.h>
#define NUM_LEDS 20
const int LED_PIN1 = 7;
LPD8806Controller<11, 13, 10> fastSpi;
RGB buffer[NUM_LEDS];
LEDFxLib ledFx(NUM_LEDS);
EffectCustom chaser(chaserEffect);

void setup()
{
	// Initialize fastSPI
	fastSpi.init();
	// Initialize LEDFx
	ledFx.init(buffer);
	// Set the FPS
	chaser.setFramerate(30);
	// Set the current effect
	ledFx.setCurrentEffect(chaser);
}

void loop()
{
	if(ledFx.update())
		fastSpi.showRGB((byte*)buffer, NUM_LEDS );
}

RGB chaserEffect(uint32_t runtime,uint16_t frameNum, uint16_t pixelNum) {
	if((frameNum % NUM_LEDS) == pixelNum)
		return cRGB(0,0,255);
	else
		return EMPTY_COLOR;
}


