// SolidColorEffect.cpp
//

#include "EffectSolidColor.h"


void EffectSolidColor::setColor(CRGB c) {
	this->baseColor = c;
}

CRGB EffectSolidColor::getColor() {
	return this->baseColor;
}

EffectSolidColor::EffectSolidColor ()
{
	this->baseColor = EMPTY_COLOR;
}
EffectSolidColor::EffectSolidColor (CRGB baseColor)
{
	this->baseColor = baseColor;
}
void EffectSolidColor::drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer) 
{
	for(int i = 0; i <context->size; i++)
		frameBuffer[i] = baseColor;
}

void EffectSolidColor::serialize(char * buffer, int size) {
	// baseColor
	ARG_TO(buffer,baseColor,CRGB);
}


void EffectSolidColor::setArgs(char* buffer) {
	baseColor = ARG_FROM(buffer,CRGB);
};

