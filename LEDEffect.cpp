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

#include "LEDEffect.h"

LEDEffect::LEDEffect() {
	setFramerate(1000, AlwaysSequential);
}

LEDEffect::LEDEffect(const LEDEffect& copy) {
	waitTime = copy.waitTime;
	lagHandling = copy.lagHandling;
	currentFrame = copy.currentFrame;
}

void LEDEffect::setFramerate (float framesPerSecond, FrameLagHandling lagHandling) {
	this->waitTime = 1000/framesPerSecond;
	this->lagHandling = lagHandling;
	currentFrame = 0;
}

void LEDEffect::reset ()
{
	currentFrame = 0;
}

bool LEDEffect::update(uint32_t tDelta, uint16_t updateCount, const LEDStripSection & context, CRGB * ledBuffer)  {
	if (tDelta >= this->waitTime) {
		// determine the current frame number
		if(lagHandling == AlwaysSequential) {
			this->currentFrame = updateCount;
		}
		//FrameLagHandling::DropMissedFrames
		else {
			this->currentFrame = tDelta / this->waitTime;
		}
		// call subclass to render to buffer.
		renderFrame(currentFrame, context, ledBuffer);
		return true;
	}
	else return false;

}
