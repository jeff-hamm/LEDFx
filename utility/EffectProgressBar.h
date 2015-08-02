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

#ifndef INC_EFFECTPROGRESSBAR_H
#define INC_EFFECTPROGRESSBAR_H
#include "Effect.h"

// A simple effect that displays values in a range of 0-255 as a progress bar from one color to another
class EffectProgressBar : public LEDEffect
{
private:
	uint16_t value;
public:
	// create an empty progress bar. Colors will go from green to red
	EffectProgressBar() { }
	EffectProgressBar(const EffectProgressBar& copy) :LEDEffect(copy), value(copy.value) { }

	// updates the progress bar by specifing a value relative to a maxium value
	void setValue(uint16_t value, uint16_t maxValue) {
		this->value = map(value, 0, maxValue, 0, UINT16_MAX);
	}
	// updates the progress bar bt specifying a float between 0 and 1.
	void setValue(float value) {
		this->value = UINT16_MAX * value;
	}

	// draw a progress bar which fades from reference color 1 to reference color 2
	void renderFrame(uint16_t currentFrame, const LEDStripSection & context, CRGB * ledBuffer)
	{
		uint16_t numLit = map(value, 0, UINT16_MAX, 0, context.size());
		for (uint16_t i = 0; i < context.size(); i++) {
			if (i < numLit) {
				ledBuffer[i] = LEDUtil::interpolate(context, 
					LEDUtil::fract16Scale(i, context.size()));
			}
			else
				ledBuffer[i] = NULL_COLOR;
		}
	}
};

#endif
