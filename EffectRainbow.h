#ifndef INC_EFFECTRAINBOW_H
#define INC_EFFECTRAINBOW_H

#include "ledeffect.h"
class EffectRainbow :
	public LEDEffect
{
public:
private:
	uint16_t rainbowWidth;
	uint8_t saturation;
	uint8_t value;
public:
	void serialize(char * buffer, int size);
	EffectRainbow();
	void setProperties(uint16_t rainbowWidth, uint8_t saturation, uint8_t value);
	bool isReversed();
	uint16_t getRainbowWidth();
	virtual void drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer);
	virtual void setArgs(char* buffer);

};
#endif

