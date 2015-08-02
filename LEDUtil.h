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

#ifndef LEDUtil_H
#define LEDUtil_H
#include "Pixel.h"
#include "LEDStripSection.h"
#include <stdint.h>
#include "lib8tion.h"

#if defined(__AVR__)
#define UINT8_MAX        ((uint8_t)0xff)
#define UINT16_MAX       ((uint16_t)0xffff)
#endif

namespace LEDUtil {

	inline CHSV interpolate(CHSV &from, CHSV & other, fract8 frac)
	{
		CHSV ret;
		from.h = lerp8by8(from.h, other.h, frac);
		from.s = lerp8by8(from.s, other.s, frac);
		from.v = lerp8by8(from.v, other.v, frac);
		return ret;
	}

	inline CHSV interpolate(CHSV & from,  CHSV & other, fract16 frac)
	{
		CHSV ret;
		from.h = lerp16by16(from.h, other.h, frac);
		from.s = lerp16by16(from.s, other.s, frac);
		from.v = lerp16by16(from.v, other.v, frac);
		return ret;
	}
	// really just renames for FastLED functions
	inline CRGB interpolate(CRGB & from, CRGB & to, fract16 scale) {
		return from.lerp16(to, scale);
	}
	inline CRGB interpolate(CRGB & from, CRGB & to, fract8 scale) {
		return from.lerp8(to, scale);
	}
	// floating point interpolation
	inline CRGB interpolate(CRGB & from, CRGB & to, float scale) {
		return interpolate(from, to, (uint16_t)(scale * UINT16_MAX));
	}

	// interpolates between the two specifid reference colors
	inline CHSV interpolate(const LEDStripSection & context, fract16 scale) {
		CHSV one = context.getRefHSV1();
		CHSV two = context.getRefHSV2();
		return interpolate(one, two, scale);
	}

	// scaling helpers
	inline fract8 fract8Scale(uint8_t value, uint8_t maxValue) {
		return (fract8)map(value, 0, maxValue, 0, UINT8_MAX);
	}
	inline fract16 fract16Scale(uint16_t value, uint16_t maxValue) {
		return (fract8)map(value, 0, maxValue, 0, UINT16_MAX);
	}


	inline  CRGB randomColor() {
		return CRGB(random(0, 256), random(0, 256), random(0, 256));
	}

	inline  CRGB randomColor(uint8_t s, uint8_t v) {
		return CHSV(random(0, 256), s, v);
	}
	// generates a random color with the saturation and luminosity value taken from the reference 
	inline  CRGB randomColor(const CHSV & referenceHSV) {
		return randomColor(referenceHSV.s, referenceHSV.v);
	}

	inline  float fpart(float x) {
		return x - (float)((long)x);
	}

	inline  float rfpart(float x) {
		return 1 - fpart(x);
	}
	inline  void swap(float & x, float & y) {
		float t = x;
		x = y;
		y = t;
	}
	// modulo which handles negative values as other languages
	inline int positive_modulo(int i, int n) {
		return (i % n + n) % n;
	}

	/*
	 void plot(int x, int y, float c, uint8_t display[][37])  {
		if (x < 37 && y < 37 && x >= 0 && y >= 0){
			int newVal = (int)(c * 255);
			if (display[x][y] + newVal > 255)
				display[x][y] = 255;
			else
				display[x][y] += newVal;
		}
	}

	 void drawLine(float x0, float y0, float x1, float y1, uint8_t display[][37]) {
		bool steep = abs(y1 - y0) > abs(x1 - x0);
		if (steep) {
			swap(x0, y0);
			swap(x1, y1);
		}
		if (x0 > x1) {
			swap(x0, x1);
			swap(y0, y1);
		}

		float dx = x1 - x0;
		float dy = y1 - y0;
		float gradient = dy / dx;

		// handle first endpoint
		float xend = round(x0);
		float yend = y0 + gradient * (xend - x0);
		float xgap = rfpart(x0 + 0.5);
		float xpxl1 = xend;  //this will be used in the main loop
		float ypxl1 = (int)yend;
		if (steep) {
			plot(ypxl1, xpxl1, rfpart(yend) * xgap, display);
			plot(ypxl1 + 1, xpxl1, fpart(yend) * xgap, display);
		}
		else {
			plot(xpxl1, ypxl1, rfpart(yend) * xgap, display);
			plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap, display);
		}
		float intery = yend + gradient; // first y-intersection for the main loop

		// handle second endpoint

		xend = round(x1);
		yend = y1 + gradient * (xend - x1);
		xgap = fpart(x1 + 0.5);
		float xpxl2 = xend; //this will be used in the main loop
		float ypxl2 = (int)yend;
		if (steep) {
			plot(ypxl2, xpxl2, rfpart(yend) * xgap, display);
			plot(ypxl2 + 1, xpxl2, fpart(yend) * xgap, display);
		}
		else {
			plot(xpxl2, ypxl2, rfpart(yend) * xgap, display);
			plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap, display);
		}

		// main loop
		for (int x = xpxl1 + 1; x < xpxl2; x++) {
			if (steep) {
				plot((int)intery, x, rfpart(intery), display);
				plot(((int)intery) + 1, x, fpart(intery), display);
			}
			else {
				plot(x, (int)intery, rfpart(intery), display);
				plot(x, ((int)intery) + 1, fpart(intery), display);
			}
			intery = intery + gradient;
		}
	}
	*/

}

#endif