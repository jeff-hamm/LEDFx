#define LEDLIB_GRB_ORDER
#include <LEDFx.h>
#include <FastSPI_LED2.h>
#define NUM_LEDS 20
LPD8806Controller<11, 13, 10> LED;
RGB buffer[NUM_LEDS];
LEDFxLib ledFx(NUM_LEDS);
EffectRandomPixels rndm;

void setup()
{
	// Initialize fastSPI
	LED.init();
	// Initialize LEDFx
	ledFx.init(buffer);
	// Set the hue and saturation
	rndm.setProperties(255,255);
	// Set the FPS
	rndm.setFramerate(8);
	// Set the current effect
	ledFx.setCurrentEffect(rndm);
}

void loop()
{
	if(ledFx.update())
		LED.showRGB((byte*)buffer, NUM_LEDS );
}
