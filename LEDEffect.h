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

#ifndef INC_LEDEffect_h
#define INC_LEDEffect_h

#include "Pixel.h"
#include "LEDStripSection.h"
#include "LEDUtil.h"

enum FrameLagHandling {
	// When AlwaysSequential is selected, frames will play in order independant of processor load. If
	// The CPU cannot keep up, the animation will show frames more slowly. This is the default option.
	AlwaysSequential,
	// When DropMissedFrames is selected, frames that would have been displayed during CPU lag will be
	// skipped. The animation will jump to whichever frame is appropriate for the current time. 
	DropMissedFrames
};

// A class encapsulating a specific LED display effect. 
class LEDEffect
{
public:
  // default constructor
  LEDEffect();
  // copy constructor
  LEDEffect(const LEDEffect&);
  // initialze the effect. 
  // framesPerSecond is the number of frames desired per second
  // If the frame order is FRAME_ORDER_TIME  the effect will tick in real time 
  //      (e.g. if the wait duration is 100ms, and the processor is only able to keep up with a 5fps framerate, it will step twice for each tick)
  // if ticktype is FRAME_ORDER_SEQUENTIAL, then duration is the total frame count and the effect will complete all frames sequentially independant of processor speed
  virtual void setFramerate(float framesPerSecond, FrameLagHandling lagHandling = AlwaysSequential);
  virtual void reset ();
  bool update(uint32_t runTime, uint16_t updateCount, const LEDStripSection & context, CRGB * ledBuffer);

protected:
	// returns the effect for the current frame number at the specified pixel
	virtual void renderFrame(uint16_t currentFrame, const LEDStripSection & context, CRGB * ledBuffer) = 0;
	// the minimum frame wait time
	uint16_t waitTime;
	// the frame processing order of this effect
	FrameLagHandling lagHandling;
	// the current frame number
	uint16_t currentFrame;

};
#endif
