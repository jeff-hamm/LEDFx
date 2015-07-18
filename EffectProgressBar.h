#ifndef INC_EFFECTPROGRESSBAR_H
#define INC_EFFECTPROGRESSBAR_H
#include "LedFxUtilities.h"
#include "LEDEffect.h"

// A simple effect that displays values in a range of 0-255 as a progress bar from one color to another
class EffectProgressBar : public LEDEffect
{
private:
	CRGB lowColor;
	CRGB highColor;
	uint8_t value;
	int numLit;
	float scale;
public:
	void serialize(char * buffer, int size);
	// create an empty progress bar. Colors will go from green to red
	EffectProgressBar ();
	EffectProgressBar (CRGB lowColor, CRGB highColor);
	// Create a solid color effect for the specified color
	void setProperties(CRGB lowColor, CRGB highColor,uint8_t value);
	void setValue(uint8_t value);
	void setFrame (uint16_t currentFrame, RangeInfoList * context);
	virtual void drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer);
	virtual void setArgs(char* buffer);
};

#endif
