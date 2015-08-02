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

#ifndef LED_STRIP_SECTION_H
#define LED_STRIP_SECTION_H
#include "Pixel.h"
#include "ReferenceColor.h"

class LEDEffect;
class LEDFxClass;

// Holds context and buffer and current effect information for a contiguous section of leds
class LEDStripSection
{
public:
	LEDStripSection(int stripOffset, uint16_t ledNumber,
		const ReferenceColor * referenceColor1 = &RAINBOW,
		const ReferenceColor * referenceColor2 = &RAINBOW_COMPLEMENT);

	// hardcoded to 2 references for now. If i convince myself I need a 3rd, I'll make it an indexed interface
	inline CHSV getRefHSV1() const { return referenceColor1.getHSVColor(); }
	inline CHSV getRefHSV2() const { return referenceColor2.getHSVColor(); }
	inline CRGB getRefRGB1() const { return referenceColor1.getRGBColor(); }
	inline CRGB getRefRGB2() const { return referenceColor2.getRGBColor(); }
	inline void setReferenceColor1(const ReferenceColor & referenceColor) { referenceColor1.referenceColor = &referenceColor; }
	inline void setReferenceColor2(const ReferenceColor & referenceColor) { referenceColor2.referenceColor = &referenceColor; }

	inline uint32_t getRunTime() const { return runTime; }
	inline LEDEffect * getEffect() const { return effect; }
	void setEffect(LEDEffect & effect);
	void reset();


	// a list of toggles that modify this strip.
	struct StripModifiers {
		bool reversed;
		bool enabled;
		StripModifiers(bool _reversed = false, bool _enabled = true) {
			reversed = _reversed;
			enabled = _enabled;
		}

		// resets the modifiers to their default values
		void reset() {
			reversed = false;
			enabled = true;
		}
	}  modifiers;

	uint16_t size() const __attribute__((always_inline)) { return ledBufferSize; }
	CRGB * leds() __attribute__((always_inline))  { return ledBuffer; }
protected:
	// provides the full LED buffer. The offset is then applied to the local pointer
	void setRawLEDBuffer(CRGB * buffer);
	// Updates this section if it is active. Returns true if an update happened
	bool update(uint32_t currentTime);

	uint16_t bufferOffset;
	CRGB * ledBuffer;
	uint16_t ledBufferSize;
	CachedReferenceColor referenceColor1;
	CachedReferenceColor referenceColor2;
	// Context values
	LEDEffect * effect;
	uint32_t startTime;
	uint32_t lastRefreshTime;
	uint16_t refreshCount;
	uint32_t runTime;
	friend class LEDFxClass;

};
#endif