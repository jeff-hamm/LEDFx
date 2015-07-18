
#ifndef EffectRandomPixels_h
#define EffectRandomPixels_h

#include "ledeffect.h"
#include "LedFxUtilities.h"
class EffectRandomPixels :
	public LEDEffect
{
private:
	bool useSatAndVal;
	uint8_t val;
	uint8_t sat;
public:
	void serialize(char * buffer, int size);
	EffectRandomPixels();
	virtual void setFrame (uint16_t frameNumber, RangeInfoList * context);
	// specify a particular saturation and luminosity value that should be used
	// when selecting random pixels.
	void setProperties(uint8_t saturation, uint8_t value);
	virtual void drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer);
	virtual void setArgs(char* buffer);
};

#endif