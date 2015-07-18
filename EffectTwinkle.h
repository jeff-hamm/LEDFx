#ifndef INC_EFFECTTWINKLE_H
#define INC_EFFECTTWINKLE_H
#include "LEDEffect.h"

// An effect with random twinkling pixels
class EffectTwinkle : public LEDEffect {
private:
	int twinkleDensity;
	uint16_t * twinklePixels;
	uint16_t * twinkleFrames;
	int twinkleWindow;
	CRGB low;
	CRGB high;
public:
	// Creates a sparsely twinkling effect
	EffectTwinkle();
	// Creates an effect with customized twinkling. Note that higher density uses more memory
	EffectTwinkle(CRGB low, CRGB high, int twinkleDensity, int twinkleWindow);
	~EffectTwinkle();
	void setColors(CRGB low, CRGB high);
	virtual void drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer);
	virtual void setArgs(char* buffer);
	void serialize(char * buffer, int size);
};

#endif