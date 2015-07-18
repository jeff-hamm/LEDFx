#ifndef INC_CUSTOMEFFECT_H
#define INC_CUSTOMEFFECT_H
#include "LEDEffect.h"

// An effect with a callback to a custom user display function
class EffectCustom : public LEDEffect {
private:
	void (*drawFrameFunc)(unsigned int, CRGB *,unsigned int);
public:
	void serialize(char * buffer, int size);
	// Creates an empty custom effect. This will do nothing unless cloned to.
	EffectCustom();
	// create an empty solid color effect. All LEDs dark
	EffectCustom(void (*drawFrameFunc)(unsigned int, CRGB *,unsigned int));

	virtual void drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer);
	virtual void setArgs(char* buffer);
};

#endif