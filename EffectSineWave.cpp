// SineWaveEffect.cpp
//

#include "EffectSineWave.h"
#include "LedFxUtilities.h"

EffectSineWave::EffectSineWave ()
{
	setColor(CRGB(0,0,0), CRGB(255,255,255));
	this->cyclePi = PI * 4.0;
	this->offset = 0;
}
EffectSineWave::EffectSineWave (CRGB baseColor, CRGB destColor, uint16_t cycles)
{
	this->cyclePi = 2* PI * (float)cycles;
	this->offset = offset;
	setColor(baseColor,destColor);
}

void EffectSineWave::setColor(CRGB baseColor, CRGB  destColor) {
	this->baseColor = baseColor;
	this->destColor = destColor;
}

void EffectSineWave::setFrame(uint16_t frameNumber, RangeInfoList * context) 
{
	LEDEffect::setFrame(frameNumber,context);
	this->numLeds = context->size;
	this->offset = context->offset;
}

void EffectSineWave::drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer) 
{
	for(int i = 0; i < context->size; i++) {
		currentFrame %= (uint16_t)numLeds;

		y = sin(cyclePi * (float)((currentFrame +offset)+ i) / (float)numLeds);
		frameBuffer[i] = LEDFxUtilities::interpolate(baseColor, destColor, (y + 1.0)/2.0);
	}
}

void EffectSineWave::serialize(char * buffer, int size) {
	// baseColor
	ARG_TO(buffer,baseColor,CRGB);
	// destColor
	ARG_TO(buffer,destColor,CRGB);
	// cyclePi
	ARG_TO(buffer,cyclePi,float);
}

void EffectSineWave::setArgs(char* buffer) {
	baseColor = ARG_FROM(buffer,CRGB);
	destColor = ARG_FROM(buffer,CRGB);
	cyclePi = ARG_FROM(buffer,float);
};

