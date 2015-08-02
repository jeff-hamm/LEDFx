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

#include "Arduino.h"
#include "Pixel.h"
#include "LEDStripSection.h"
#include "LEDFxClass.h"

LEDStripSection::LEDStripSection(int offset, uint16_t _ledBufferSize,
	const ReferenceColor * _referenceColor1, const ReferenceColor * _referenceColor2) :
	modifiers(), bufferOffset(offset), ledBuffer(NULL), ledBufferSize(_ledBufferSize), referenceColor1(CachedReferenceColor(_referenceColor1)),
	referenceColor2(CachedReferenceColor(_referenceColor2)), effect(NULL), startTime(0), lastRefreshTime(0), refreshCount(0), runTime(0) {
}


static void reverse(CRGB * buffer, int size) {
	for (int i = 0; i < size / 2; i++)
	{
		CRGB tmp = buffer[i];
		buffer[i] = buffer[(size - 1) - i];
		buffer[(size - 1) - i] = tmp;
	}
}

bool LEDStripSection::update(uint32_t currentTime)
{
	runTime = currentTime - startTime;
	if (modifiers.enabled && effect) {
		referenceColor1.update(runTime);
		referenceColor2.update(runTime);
		if (effect->update(runTime - lastRefreshTime, refreshCount, *this, ledBuffer)) {
			lastRefreshTime = runTime;
			refreshCount++;
			if (modifiers.reversed)
				reverse(ledBuffer, ledBufferSize);
			return true;
		}

	}
	return false;
}

void LEDStripSection::reset() {
	startTime = 0;
	effect = NULL;
	lastRefreshTime = 0;
	refreshCount = 0;
	runTime = 0;
	modifiers.reset();
}

void LEDStripSection::setRawLEDBuffer(CRGB * buffer) {
	ledBuffer = &buffer[bufferOffset];
}


void LEDStripSection::setEffect(LEDEffect & _effect) {
	effect = &_effect;
	startTime = millis();
	lastRefreshTime = 0;
	refreshCount = 0;
	runTime = 0;
}
