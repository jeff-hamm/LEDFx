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

#ifndef INC_SOLIDCOLOREFFECT_H
#define INC_SOLIDCOLOREFFECT_H

#include "Effect.h"

// A simple effect that displays a static color over the range
class EffectSolidColor : public LEDEffect
{
public:
	// Create a solid color effect for the specified color
	EffectSolidColor();
	void renderFrame(uint16_t currentFrame, const LEDStripSection & context, CRGB * ledBuffer)
	{
		fill_solid(ledBuffer, context.size(), context.getRefRGB1());
	}
};


#endif
