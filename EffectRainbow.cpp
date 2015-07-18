#include "EffectRainbow.h"
#include "LedFxUtilities.h"

void EffectRainbow::setProperties(uint16_t rainbowWidth, uint8_t saturation, uint8_t value) {
	this->rainbowWidth = rainbowWidth;
	this->saturation = saturation;
	this->value = value;
}

uint16_t EffectRainbow::getRainbowWidth() {
	return this->rainbowWidth;
}

EffectRainbow::EffectRainbow ()
{
	this->rainbowWidth = 64;
	this->saturation = 255;
	this->value = 255;
}

void EffectRainbow::drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer) 
{
	for(int i = 0; i < context->size; i++) {
		uint8_t h = map((currentFrame + i) % rainbowWidth,0,rainbowWidth,0,255);
		frameBuffer[i] = LEDFxUtilities::HSVtoRGB(h, saturation, value);
	}
}

void EffectRainbow::serialize(char * buffer, int size) {
	// rainbowWidth
	ARG_TO(buffer,rainbowWidth,uint16_t);
	//saturation
	ARG_TO(buffer,saturation,uint8_t);
	// value
	ARG_TO(buffer,value,uint8_t);
	
}


void EffectRainbow::setArgs(char* buffer) {
	this->rainbowWidth  = ARG_FROM(buffer, unsigned int);
	this->saturation  = ARG_FROM(buffer, unsigned int);
	this->value  = ARG_FROM(buffer, unsigned int);
};

