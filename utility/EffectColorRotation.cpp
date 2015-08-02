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

#include "EffectColorRotation.h"
#include "Effect.h"


// create an empty color gradient effect. All LEDs dark
EffectColorRotation::EffectColorRotation (uint16_t colorDuration, uint16_t fadeDuration) :
currentColor(NULL_COLOR), nextColor(NULL_COLOR), frameDuration(colorDuration),
fadeDuration(fadeDuration), lastChange(0)
{
}

EffectColorRotation::EffectColorRotation(EffectColorRotation&copy) : LEDEffect(copy),
currentColor(copy.currentColor), nextColor(copy.nextColor), frameDuration(copy.frameDuration), 
fadeDuration(copy.fadeDuration), lastChange(copy.lastChange)
{
}

void EffectColorRotation::reset() {
	LEDEffect::reset();
	lastChange = 0;
}

void EffectColorRotation::updateRotation(uint16_t currentFrame,const LEDStripSection & context) {
	if (this->currentColor == NULL_COLOR)
		this->currentColor = getNextColor(context);
	if(currentFrame >=  lastChange + frameDuration) {
			// if completely done
		if(currentFrame >= (lastChange + frameDuration + fadeDuration)) {
			lastChange = currentFrame;
			// if we haven't picked the next color, do so
			if(this->nextColor == NULL_COLOR) 
				this->nextColor = getNextColor(context);
			this->currentColor = nextColor;
			this->nextColor = NULL_COLOR;
		}
		// actively fading to nextcolor
		else {
			// if we haven't picked the next color, do so
			if(this->nextColor == NULL_COLOR)
				this->nextColor = getNextColor(context);
			// now interpolate
			this->currentColor = LEDUtil::interpolate(
				currentColor, nextColor, LEDUtil::fract16Scale((currentFrame - (lastChange + frameDuration)), fadeDuration));
		}

	}
}
inline CRGB EffectColorRotation::getNextColor(const LEDStripSection & context) {
	return LEDUtil::randomColor(context.getRefHSV1());
}

void EffectColorRotation::renderFrame(uint16_t currentFrame,const LEDStripSection & context, CRGB * ledBuffer) {
	updateRotation(currentFrame, context);
	fill_solid(ledBuffer, context.size(), currentColor);
}
