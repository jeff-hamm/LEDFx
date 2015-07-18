#include "EffectRandomPixels.h"

EffectRandomPixels::EffectRandomPixels() {
  useSatAndVal = false;
}
void EffectRandomPixels::setProperties(uint8_t sat, uint8_t val) {
  useSatAndVal = true;
  this->sat = sat;
  this->val = val;
}

void EffectRandomPixels::setFrame (uint16_t frameNumber, RangeInfoList * context) {

}


void EffectRandomPixels::drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer) 
{
	for(int i = 0; i < context->size; i++) {
	  if(useSatAndVal)
		frameBuffer[i] = LEDFxUtilities::randomColor(sat,val);
	  else
		frameBuffer[i] = LEDFxUtilities::randomColor();
	}
}


void EffectRandomPixels::serialize(char * buffer, int size) {
	// sat
	ARG_TO(buffer,sat,uint8_t);
	// val
	ARG_TO(buffer,val,uint8_t);
}

void EffectRandomPixels::setArgs(char* buffer) {
  useSatAndVal = true;
  this->sat = ARG_FROM(buffer,uint8_t);	
  this->val = ARG_FROM(buffer,uint8_t);

  if(sat != 0 || val != 0)
	  useSatAndVal = true;
  else
	  useSatAndVal = false;
}

