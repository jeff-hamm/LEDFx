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

#ifndef INC_SINEWAVEEFFECT_H
#define INC_SINEWAVEEFFECT_H

#include "Effect.h"

// A sine wave lighting effect that carries from dark to white through a particular color
class EffectSineWave : public LEDEffect
{
private:
	float cyclePi;
	uint16_t offset;
public:
	// Create a sinewave effect for the specified led range, passing through the desired baseColor 
	// cycles number of times accross that range.
	EffectSineWave(uint16_t cycles = 4, int offset = 0) {
		this->cyclePi = 2.0 * PI * (float)cycles;
		this->offset = offset;
	}
	EffectSineWave(const EffectSineWave& copy) : LEDEffect(copy), cyclePi(copy.cyclePi), offset(copy.offset) {}

	void renderFrame(uint16_t currentFrame, const LEDStripSection & context, CRGB * ledBuffer)
	{
		currentFrame %= context.size();
		for (uint16_t i = 0; i < context.size(); i++) {
			uint16_t y = UINT16_MAX / 2 + sin16(cyclePi * LEDUtil::fract16Scale(((currentFrame)+i), context.size()));
			ledBuffer[i] = LEDUtil::interpolate(context, y);
		}
	}

};
#endif