#ifndef INC_SOLIDCOLOREFFECT_H
#define INC_SOLIDCOLOREFFECT_H
#include "LEDEffect.h"

// A simple effect that displays a static color over the range
class EffectSolidColor : public LEDEffect
{
private:
	CRGB baseColor;
public:
	void serialize(char * buffer, int size);
	void setColor(CRGB c);
	CRGB getColor();
	// create an empty solid color effect. All LEDs dark
	EffectSolidColor ();
	// Create a solid color effect for the specified color
	EffectSolidColor (CRGB baseColor);
	virtual void drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer);
	virtual void setArgs(char* buffer);
};

#endif
