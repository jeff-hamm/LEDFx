#include "FastLED.h"
#include "LEDFx.h"

#define NUM_LEDS 20
const int LED_PIN = 17;

CRGB leds[NUM_LEDS];
EffectSineWave sinWave;

void setup() {
	LEDS.addLeds<WS2811, LED_PIN, BRG>(leds, NUM_LEDS);
	// Initialize LEDFx
	LEDFx.init(leds, NUM_LEDS);

	// Set the current effect
	LEDFx.setEffect(sinWave);
}

void loop() {
	if (LEDFx.update()) {
		LEDS.show();
	}
}