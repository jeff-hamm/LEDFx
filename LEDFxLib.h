#ifndef INC_LEDFXLIB_H
#define INC_LEDFXLIB_H
#include "LedFxUtilities.h"
#include "LEDEffect.h"
#include "RangeInfoList.h"
#include "Pixel.h"


/* 
* A library that provides high level control of LED strip display functions 
* Works in conjunction with the fastSPI library. 
*/
class LEDFx {
private:
	struct CRGB *leds;
	RangeInfoList currentList;
	uint16_t ledNum;

public:

	LEDFx(uint16_t ledNum);
	~LEDFx();
	// removes all of the associated effects.
	void clear();
	// Initializes the library. You _must_ have initialized fastSPI before this call!
	void init(CRGB * leds);

	//defines a range with the specified identifier in the specified location
	// use this identifier elsewhere to 
	// returns null if the specified range ID has already been used.
	RangeInfoList* addRange(int rangeId, uint16_t offset, uint16_t size, bool reversed = false);

	// Adds an effect. If a range is not specified, this spans the entire LED strip, if a range is specified. Only that section will be used
//	void setEffectSequence(LEDEffectSequence & sequence, int rangeId=-1);

	// Clears the effect on the specified range
	void clearCurrentEffect(int rangeId=-1);

	// Sets 1 effect to display. This will overwrite anything added by the 'addEffect' call. 
	void setCurrentEffect(LEDEffect & effect, int rangeId=-1);

	// Sets 1 effect to display. This will overwrite anything added by the 'addEffect' call. 
	void setCurrentEffectWithArgs(LEDEffect & effect, int rangeId=-1);

	// gets the currently displaying effect
	IDrawable * getCurrentEffect(int rangeId=-1);

	// iterates the effects over time
	bool update();
};

#endif