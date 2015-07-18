#include "LEDFxLib.h"
#ifdef __AVR_ATmega328P__
#include "new.h"
#endif

LEDFx::LEDFx(uint16_t ledNum) : 
	currentList(0,0,ledNum),
	ledNum(ledNum)
{
}
LEDFx::~LEDFx() {
	clear();
}

// removes all of the associated effects.
void LEDFx::clear() {
	currentList.clear();
}

// Initializes the library. You _must_ have initialized fastSPI before this call!
void LEDFx::init(CRGB* leds)
{
	this->leds = leds; 
	currentList.clear();
}

// defines a range with the specified range identifier in the specified strip location
// use this identifier elsewhere to reference this range
RangeInfoList* LEDFx::addRange(int rangeId, uint16_t offset, uint16_t size, bool reversed) {
	if(!currentList.containsRange(rangeId)) {
		return currentList.add(rangeId, offset, size, reversed);
	}
	else
		return NULL;
}

// Adds an effect. If a range is not specified, this spans the entire LED strip, if a range is specified. Only that section will be used
//void LEDFx::setEffectSequence(LEDEffectSequence &sequence, int rangeId) {
//	currentList.setEffect(rangeId, sequence);
//}

// Sets 1 effect to display. This will overwrite anything added by the 'addEffect' call.
void LEDFx::clearCurrentEffect(int rangeId) {
	currentList.clearEffect(rangeId);
}

// Sets 1 effect to display. This will overwrite anything added by the 'addEffect' call.
void LEDFx::setCurrentEffect(LEDEffect &effect, int rangeId) {
	if(rangeId == -1)
		currentList.clearAll();
	currentList.setEffect(rangeId, effect);
}

// Sets 1 effect to display. This will overwrite anything added by the 'addEffect' call.
void LEDFx::setCurrentEffectWithArgs(LEDEffect & effect, int rangeId) {
	currentList.setEffectWithArgs(rangeId, effect);
}


// Sets 1 effect to display. This will overwrite anything added by the 'addEffect' call.
IDrawable* LEDFx::getCurrentEffect(int rangeId) {
	return currentList.getEffect(rangeId);
}




// iterates the effects over time
bool LEDFx::update() {
	RangeInfoList *cur = &currentList;
	uint32_t runTime = millis() - cur->startTime;
	bool anyUpdate = false;
	do {
		if (cur->listItem != NULL && cur->listItem->update(runTime, leds, cur)) {
			anyUpdate = true;
			cur->refreshCount++;
			cur->lastRefreshTime = runTime;
		}
		cur = cur->next;
	}
	while(cur != NULL);
	return anyUpdate;
}
