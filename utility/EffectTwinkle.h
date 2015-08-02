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

#ifndef INC_EFFECTTWINKLE_H
#define INC_EFFECTTWINKLE_H
#include "Effect.h"
struct TwinklePixel {
	uint16_t pixelIndex;
	uint16_t frameStart;
	uint16_t frameEnd;
	TwinklePixel() {
		pixelIndex = 0;
		frameStart = 0;
		frameEnd = 0;
	}
};

// An effect with random twinkling pixels. 'Twinkling' is defines as sputtering between Reference Color 1 and Reference Color 2 rapidly.
// maxTwinkles determines the number of pixels that can be queued to 'twinkle' in a given timeframe. The higher this number, the more
// frequent the twinkling effect (relative to a constant twinkleWindow), but the more memory this uses.
template<int maxTwinklePixels>
class EffectTwinkle : public LEDEffect {
public:
	// Creates an effect with customized twinkling. Note that higher density uses more memory (4 bytes per density value)
	// the default effect is extremely sparse.
	// TwinkleWindow determines the number of frames during which twinkleDensity pixels will 'twinkle'. A long window and a low
	// density means that pixels will twinkle rarely. A high density and short window means that many pixels will be blinking 
	// frequently
	// twinkleDuration determines exactly how long pixels twinkle for.
	EffectTwinkle(uint16_t twinkleWindow = 360, uint16_t twinkleDuration = 40);
	EffectTwinkle(const EffectTwinkle&);

	virtual void renderFrame(uint16_t currentFrame, const LEDStripSection & context, CRGB * ledBuffer);
private:
	void checkTwinklePixels(uint16_t currentFrame, const LEDStripSection & context);
	uint16_t twinkleWindow;
	uint16_t twinkleDuration;
	TwinklePixel twinklePixels[maxTwinklePixels];
};



template<int density>
EffectTwinkle<density>::EffectTwinkle(uint16_t twinkleWindow, uint16_t twinkleDuration) :
twinkleWindow(twinkleWindow), twinkleDuration(twinkleDuration) { 
	for (int i = 0; i < density; i++) {
		twinklePixels[i] = TwinklePixel();
	}
}

template<int density>
EffectTwinkle<density>::EffectTwinkle(const EffectTwinkle & copy) :
twinkleWindow(copy.twinkleWindow), twinkleDuration(copy.twinkleDuration) { 
	for (int i = 0; i < density; i++)
		twinklePixels[i] = copy.twinklePixels;
}

bool afterRange(TwinklePixel & p, uint16_t currentFrame) {
	return (int32_t)(p.frameEnd - currentFrame) > 0 && (int32_t)(p.frameStart - currentFrame) >= 0;
}
bool inRange(TwinklePixel & p, uint16_t currentFrame) {
	return (int32_t)(p.frameEnd - currentFrame) < 0 && (int32_t)(p.frameStart - currentFrame) >= 0;
}
template<int density>
void EffectTwinkle<density>::checkTwinklePixels(uint16_t currentFrame, const LEDStripSection & context) {
	for (int i = 0; i < density; i++) {
		TwinklePixel & p = twinklePixels[i];
		if (afterRange(p,currentFrame)) {
			p.frameStart = currentFrame + random(0, twinkleWindow);
			p.frameEnd = p.frameStart + random(twinkleDuration / 2, twinkleDuration*1.5);
			p.pixelIndex = random(0, context.size());
		}
	}
}

template<int density>
void EffectTwinkle<density>::renderFrame(uint16_t currentFrame, const LEDStripSection & context, CRGB * ledBuffer) {
	checkTwinklePixels(currentFrame, context);
	fill_solid(ledBuffer, context.size(), context.getRefRGB1());
	for (int i = 0; i < density; i++) {
		TwinklePixel & p = twinklePixels[i];
		if (inRange(p,currentFrame)) {
			ledBuffer[p.pixelIndex] = currentFrame % 2 == 0 ? context.getRefRGB1() : context.getRefRGB2();
		}
	}
}
#endif