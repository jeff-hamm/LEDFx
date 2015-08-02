/*
Copyright 2015 Jeff Hamm <jeff.hamm@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef EffectRandomPixels_h
#define EffectRandomPixels_h

#include "Effect.h"

// renders random leds over the section with hue and saturation based on referencecolor1
class EffectRandomPixels :
	public LEDEffect
{
public:
	EffectRandomPixels() {}
	virtual void renderFrame(uint16_t currentFrame, const LEDStripSection & context, CRGB * ledBuffer)
	{
		for (uint16_t i = 0; i < context.size(); i++) {
			ledBuffer[i] = LEDUtil::randomColor(context.getRefHSV1());
		}
	}


};

#endif