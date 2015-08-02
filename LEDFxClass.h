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

#ifndef INC_LEDFXLIB_H
#define INC_LEDFXLIB_H
#include "Pixel.h"
#include "LEDUtil.h"
#include "LEDEffect.h"
#include "LinkedList.h"
#include "utility/EffectSineWave.h"

/* 
* A library that provides high level control of LED strip display functions 
* Calls against this class affect the entire LED strip. Use the 'addSection' method
* to partition the strip
*/
class LEDFxClass : public LEDStripSection {
private:
	LinkedListNode<LEDStripSection> currentList;
	EffectSineWave defaultEffect;
public:

	LEDFxClass();
	~LEDFxClass();

	void init(CRGB * leds, uint16_t ledNum);
	// removes all of the associated effects.
	void removeSections();

	//defines a range with the specified identifier in the specified location
	void addSection(LEDStripSection & range);

	// iterates the effects over time
	bool update();
};

extern LEDFxClass LEDFx;

#endif