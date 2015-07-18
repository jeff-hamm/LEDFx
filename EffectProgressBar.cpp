// EffectProgressBar.cpp
//

#include "EffectProgressBar.h"


void EffectProgressBar::setProperties(CRGB lowColor, CRGB highColor, uint8_t value) {
	this->lowColor = lowColor;
	this->highColor = highColor;
	this->value = value;
}

void EffectProgressBar::setValue(uint8_t value) {
	this->value = value;
}


EffectProgressBar::EffectProgressBar ()
{
	setProperties(CRGB(0,255,0), CRGB(255,0,0),0);
}
EffectProgressBar::EffectProgressBar (CRGB lowColor, CRGB highColor)
{
	setProperties(lowColor, highColor, 0);
}

void EffectProgressBar::setFrame (uint16_t currentFrame, RangeInfoList * context) {
	numLit = map(value,0,255,0,context->size);
	scale = 1.0/((float)context->size);		
}

void EffectProgressBar::drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer) 
{
	for(int i = 0; i < context->size; i++) {
		if(i < numLit) 
			frameBuffer[i] =  LEDFxUtilities::interpolate(lowColor,highColor, (float)i*scale);
		else
			frameBuffer[i] =  EMPTY_COLOR;
	}
}

void EffectProgressBar::serialize(char * buffer, int size) {
	// lowColor
	ARG_TO(buffer,lowColor,CRGB);
	// highColor
	ARG_TO(buffer,highColor,CRGB);
	// value
	ARG_TO(buffer,value,uint8_t);
}


void EffectProgressBar::setArgs(char* buffer) {
	lowColor = ARG_FROM(buffer,CRGB);
	highColor = ARG_FROM(buffer,CRGB);
	value = ARG_FROM(buffer,uint8_t);
};

