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

#ifndef INC_EFFECTRAINBOW_H
#define INC_EFFECTRAINBOW_H
#include "Effect.h"

// Spans a rainbow across the strip. The number of virtual pixels in the rainbow is set by rainbow width
// The hue and saturation of the rainbow is determined by referencecolor1
class EffectRainbow : public LEDEffect
{
public:
	EffectRainbow(uint16_t rainbowWidth = 64) : rainbowWidth(rainbowWidth) { }
	EffectRainbow(const EffectRainbow& copy) : LEDEffect(copy), rainbowWidth(copy.rainbowWidth) {}
	void setRainbowWidth(uint16_t rainbowWidth) { this->rainbowWidth = rainbowWidth; }
	uint16_t getRainbowWidth() { return this->rainbowWidth; }
	void renderFrame(uint16_t currentFrame, const LEDStripSection & context, CRGB * ledBuffer)
	{
		for (uint16_t i = 0; i < context.size(); i++) {
			uint8_t h = map((currentFrame + i) % rainbowWidth, 0, rainbowWidth - 1, 0, 255);
			ledBuffer[i] = CHSV(h, context.getRefHSV1().s, context.getRefHSV1().v);
		}
	}
private:
	uint16_t rainbowWidth;

};
#endif

