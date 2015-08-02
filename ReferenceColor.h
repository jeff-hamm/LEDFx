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

#ifndef REFERENCE_COLOR_H
#define REFERENCE_COLOR_H
#include "Pixel.h"

// Holds on to either a dynamic or static color to be referenced by color effects
class ReferenceColor {
public:
	virtual CHSV getColor(uint32_t runTime) const = 0;
};

typedef CHSV(*HSVTimeFunc)(uint32_t runTime);
class DynamicReferenceColor : public ReferenceColor {
public:

	DynamicReferenceColor(HSVTimeFunc colorFunction) {
		setColorFunction(colorFunction);
	}
	virtual CHSV getColor(uint32_t runTime) const {
		if (dynamicColor)
			return dynamicColor(runTime);
		else
			return NULL_HSV;
	}

	inline ReferenceColor& operator= (const HSVTimeFunc& rhs) __attribute__((always_inline))
	{
		setColorFunction(rhs);
		return *this;
	}

protected:
	void setColorFunction(HSVTimeFunc colorFunction) {
		dynamicColor = colorFunction;
	}
	HSVTimeFunc dynamicColor;
};

class StaticReferenceColor : public ReferenceColor {
public:
	StaticReferenceColor(CHSV color) {
		setColor(color);
	}

	virtual CHSV getColor(uint32_t runTime) const {
		return staticColor;
	}
	
	inline ReferenceColor& operator= (const CHSV& rhs) __attribute__((always_inline))
	{
		setColor(rhs);
		return *this;
	}
protected:
	void setColor(const CHSV color) {
		staticColor = color;
	}
	CHSV staticColor;
};

typedef CHSV(*HSVRelativeTimeFunc)(const ReferenceColor& relativeTo, uint32_t runTime);
class RelativeReferenceColor : public ReferenceColor {
public:
	RelativeReferenceColor(HSVRelativeTimeFunc colorFunction, const ReferenceColor & relativeColor) : 
		dynamicRelativeColor(colorFunction), relativeTo(relativeColor) {
	}

	virtual CHSV getColor(uint32_t runTime) const {
		if (dynamicRelativeColor)
			return dynamicRelativeColor(relativeTo, runTime);
		else
			return NULL_HSV;
	}

protected:
	HSVRelativeTimeFunc dynamicRelativeColor;
	const ReferenceColor & relativeTo;
};

template <uint32_t duration, uint8_t saturation, uint8_t value, bool smooth>
CHSV getRainbow(uint32_t currentTime) {
	uint8_t hue = map(currentTime % duration, 0, duration - 1, 0, 256);
	// if we're smoothing, bounce backwards on odd cycles.
	if (smooth && (currentTime / duration) & 0x01)
		hue = 255 - hue;
	return CHSV(hue, saturation, value);
}

template<int duration, uint8_t saturation, uint8_t value, bool smoothRainbow>
inline DynamicReferenceColor getRainbowReference() {
	return &getRainbow<duration, saturation, value, smoothRainbow>;
}

inline CHSV getComplement(const ReferenceColor& color, uint32_t runTime) {
	CHSV relative = color.getColor(runTime);
	return CHSV((uint8_t)(relative.h + 128), relative.s, relative.v);
}

inline RelativeReferenceColor getComplementReference(const ReferenceColor& color) {
	return RelativeReferenceColor(&getComplement, color);
}

const DynamicReferenceColor FAST_RAINBOW = DynamicReferenceColor(&getRainbow<1000, 255, 255, true>);
const RelativeReferenceColor FAST_RAINBOW_COMPLEMENT = RelativeReferenceColor(&getComplement, FAST_RAINBOW);
const DynamicReferenceColor RAINBOW = DynamicReferenceColor(&getRainbow<10000, 255, 255, true>);
const RelativeReferenceColor RAINBOW_COMPLEMENT = RelativeReferenceColor(&getComplement, RAINBOW);
const DynamicReferenceColor SLOW_RAINBOW = DynamicReferenceColor(&getRainbow<100000, 255, 255, true>);
const RelativeReferenceColor SLOW_RAINBOW_COMPLEMENT = RelativeReferenceColor(&getComplement, SLOW_RAINBOW);

class CachedReferenceColor {
public:
	CachedReferenceColor(const ReferenceColor * referenceColor = NULL) : referenceColor(referenceColor) { }
	void update(uint32_t runTime) {
		if (referenceColor) {
			cacheHSV = referenceColor->getColor(runTime);
			cacheRGB = cacheHSV;
		}
	}
	const ReferenceColor * referenceColor;
	inline CRGB getRGBColor() const __attribute__((always_inline)) { return cacheRGB; }
	inline CHSV getHSVColor() const __attribute__((always_inline)) { return cacheHSV; }
protected:
	CRGB cacheRGB;
	CHSV cacheHSV;
};

#endif