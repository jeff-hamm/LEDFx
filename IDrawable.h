// IDrawable.h

#ifndef _IDRAWABLE_h
#define _IDRAWABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Pixel.h"
#include "RangeInfoList.h"
#include <stdarg.h>

class IDrawable
{
 public:
	// Serialize the current state to the buffer, not to exceed the specified size
	virtual void serialize(char * buffer, int size) = 0;
	virtual bool update(uint32_t runTime, CRGB* buffer, RangeInfoList* context) = 0;
};


#endif

