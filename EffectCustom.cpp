#include "EffectCustom.h"

// Creates an empty custom effect. This will do nothing unless cloned to.
EffectCustom::EffectCustom() {
	drawFrameFunc = NULL;
}
// create an empty solid color effect. All LEDs dark
EffectCustom::EffectCustom(void (*drawFrameFunc)(unsigned int, CRGB *,unsigned int)) {
	this->drawFrameFunc = drawFrameFunc;
}

void EffectCustom::drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer) {
	if(drawFrameFunc != NULL)
		return drawFrameFunc(currentFrame, frameBuffer, context->size);
}

void EffectCustom::serialize(char * buffer, int size) {
}

void EffectCustom::setArgs(char* buffer) {
};
