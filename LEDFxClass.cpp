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

#include "LEDFxClass.h"

LEDFxClass LEDFx;

LEDFxClass::LEDFxClass() :
LEDStripSection(0, 0), currentList(this)
{
}

LEDFxClass::~LEDFxClass() {
	removeSections();
}

void LEDFxClass::init(CRGB* _leds, uint16_t _ledCount) {
	this->ledBuffer = _leds;
	this->ledBufferSize = _ledCount;
	currentList.add(this);
	this->setEffect(defaultEffect);
}

// removes all additional sections outside of the global one.
void LEDFxClass::removeSections() {
	currentList.deleteRest();
}

// defines a range with the specified range identifier in the specified strip location
// use this identifier elsewhere to reference this range
void LEDFxClass::addSection(LEDStripSection & section) {
	if (!currentList.contains(&section)) {
		// disable the global strip once we start using a custom one
		modifiers.enabled = false;
		section.setRawLEDBuffer(this->ledBuffer);
		currentList.add(&section);
	}
}



// iterates the effects over time
bool LEDFxClass::update() {
	LinkedListNode<LEDStripSection> *cur = &currentList;
	uint32_t currentTime = millis();
	bool anyUpdate = false;
	do {
		if (cur && cur->value && cur->value->update(currentTime))
			anyUpdate = true;
		cur = cur->next;
	}
	while(cur);
	return anyUpdate;
}
