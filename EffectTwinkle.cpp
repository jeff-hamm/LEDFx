#include "EffectTwinkle.h"

// Creates an empty custom effect. This will do nothing unless cloned to.
EffectTwinkle::EffectTwinkle() {
	twinkleDensity = 2;
	twinklePixels = (uint16_t*)calloc(twinkleDensity ,sizeof(uint16_t));
	twinkleFrames = (uint16_t*)calloc(twinkleDensity ,sizeof(uint16_t));
	twinkleWindow = 360;
	low = EMPTY_COLOR;
	high = CRGB(255,255,255);
}
// create an empty solid color effect. All LEDs dark
EffectTwinkle::EffectTwinkle(CRGB low, CRGB high, int twinkleDensity, int twinkleWindow) {
	this->low = low;
	this->high = high;
	this->twinkleDensity = twinkleDensity;
	this->twinkleWindow = twinkleWindow;
	twinklePixels = (uint16_t*)calloc(twinkleDensity,sizeof(uint16_t));
	twinkleFrames = (uint16_t*)calloc(twinkleDensity ,sizeof(uint16_t));
}
EffectTwinkle::~EffectTwinkle() {
	free(twinklePixels);
	free(twinkleFrames);
}
void EffectTwinkle::setColors(CRGB low, CRGB high) {
	this->low = low;
	this->high = high;
}

void EffectTwinkle::drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer) {
	uint16_t currentPosition = (currentFrame % twinkleWindow);
	// fill the twinklebuffer with the start-twinkling framenumber
	if(currentPosition == 0) {
		for(int i = 0; i < twinkleDensity; i++) {
			twinklePixels[i] = random(0,context->size);
			twinkleFrames[i] = random(0,twinkleWindow);
		}
	}
	for(int i = 0; i < context->size; i++)
		frameBuffer[i] = low;
	int duration = (1000/this->waitTime);
	for(int i = 0; i < twinkleDensity; i++) {
		if(currentPosition > twinkleFrames[i] && (currentPosition < twinkleFrames[i]+duration)) {
			frameBuffer[twinklePixels[i]] = currentPosition % 2 == 0 ? low : high;
		}
	}
}

void EffectTwinkle::serialize(char * buffer, int size) {
}

void EffectTwinkle::setArgs(char* buffer) {
};
