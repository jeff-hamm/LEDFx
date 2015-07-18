// LEDEffect.cpp
//

#include "LEDEffect.h"

LEDEffect::LEDEffect() {
	setFramerate(1000, FRAME_ORDER_SEQUENTIAL);
}

void LEDEffect::setFramerate (float framesPerSecond, frame_order frameOrder) {
	this->waitTime = 1000/framesPerSecond;
	this->frameOrder = frameOrder;
	currentFrame = 0;
}

void LEDEffect::reset ()
{
	currentFrame = 0;
}

void LEDEffect::setFrame (uint16_t currentFrame, RangeInfoList* context)
{
	this->currentFrame = currentFrame;
	this->context = context;
	if(context->hasArgs)
		this->setArgs(context->contextArgs);
}

void reverse(CRGB * buffer, int size) {
	for(int i = 0; i < size/2; i++)
	{
		CRGB tmp = buffer[i];
		buffer[i] = buffer[(size-1)-i];
		buffer[(size-1)-i] = tmp;
	}
}


bool LEDEffect::update(uint32_t runTime, CRGB* buffer, RangeInfoList * context)  {
	if((runTime - context->lastRefreshTime) > this->waitTime) {
		if(frameOrder == FRAME_ORDER_SEQUENTIAL) {
			setFrame(context->refreshCount, context);
		}
		else {
			setFrame((runTime - context->startTime) / this->waitTime, context);
		}
		drawFrame(currentFrame, context, &buffer[context->offset]);
		if(context->reversed)
			reverse(&buffer[context->offset], context->size); 
		return true;
	}
	return false;

}
