#ifndef INC_SINEWAVEEFFECT_H
#define INC_SINEWAVEEFFECT_H
#include "LEDEffect.h"

// A sine wave lighting effect that carries from dark to white through a particular color
class EffectSineWave : public LEDEffect
{
private:
	uint16_t numLeds;
	CRGB baseColor;
	CRGB destColor;
	float y;
	float cyclePi;
	uint16_t offset;
public:
	void serialize(char * buffer, int size);
	void setColor(CRGB baseColor, CRGB destColor);
	// Create a sine wave effect. This will not function unless it is cloned to
	EffectSineWave ();
	// Create a sinewave effect for the specified led range, passing through the desired baseColor 
	// cycles number of times accross that range.
	EffectSineWave (CRGB baseColor, CRGB destColor, uint16_t cycles);
	virtual void setFrame (uint16_t frameNumber, RangeInfoList * context);
	virtual void drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer);
	virtual void setArgs(char* buffer);
};
#endif
