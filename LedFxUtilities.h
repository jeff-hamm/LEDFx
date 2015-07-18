#ifndef INC_LedFxUtilities_H
#define INC_LedFxUtilities_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif
#include "Pixel.h"


class LEDFxUtilities { 
public:

static CRGB interpolate_fp(CRGB from, CRGB to, unsigned char scale) {
  CRGB retVal;
  int iScale = scale+1;
  retVal.r = from.r + ((((int)to.r - (int)from.r)*iScale) >> 8);
  retVal.g = from.g + ((((int)to.g - (int)from.g)*iScale) >> 8);
  retVal.b = from.b + ((((int)to.b - (int)from.b)*iScale) >> 8);
  return retVal;
}

static CRGB interpolate(CRGB from, CRGB to, float scale) {
  CRGB retVal;
  retVal.r = from.r + ((float)(to.r - from.r) * scale);
	retVal.g = from.g + ((float)(to.g - from.g) * scale);
	retVal.b = from.b + ((float)(to.b - from.b) * scale);
  return retVal;

}

static CRGB interpolate(CRGB from, CRGB to, uint16_t steps, uint16_t step) {
  CRGB retVal;
  float scale = 1.0/(float)steps;

  if(step == 0 )
	  return from;
  else {

	  retVal.r = from.r + ((float)(to.r - from.r) * scale);
		retVal.g = from.g + ((float)(to.g - from.g) * scale);
		retVal.b = from.b + ((float)(to.b - from.b) * scale);
	  return retVal;
  }
}


static CRGB randomColor() {
    return CRGB(random(1,255),random(1,255),random(1,255));
  }

static CRGB randomColor(uint8_t s,uint8_t v) {
  return HSVtoRGB(random(0,256),s,v);
}

static void RGBToHSV(CRGB rgb, uint8_t & h, uint8_t & s, uint8_t v) {
	uint8_t M = max(max(rgb.r,rgb.g),rgb.b);
	uint8_t m = min(min(rgb.r,rgb.g),rgb.b);
	int C = M-m;
	int hPrime;
	if(C == 0)
		hPrime = 0;
	else if ( M == rgb.r)
		hPrime = ((((int)rgb.g - (int)rgb.b))/C);
	else if ( M == rgb.g) 
		hPrime = ((((int)rgb.b - (int)rgb.r))/C) + 2;
	else if ( M == rgb.b) 
		hPrime = ((((int)rgb.r - (int)rgb.g))/C) + 4;
	h = hPrime * 42.5;

	v = M;
	if(C == 0)
		s = 0;
	else {
		s = (C*255)/v;
	}

}
// converts hue, saturation, value to CRGB
static CRGB HSVtoRGB(uint8_t  h, uint8_t s,  uint8_t v) {
	CRGB retVal;
	hsv2rgb_rainbow( CHSV(h,s,v), retVal);
	return retVal;
/*  uint8_t h_i = h/42.5;
  uint16_t c = (s*v)/255;
  int m = v - c;
  uint8_t x =  (c/42.5)*(42.5 - (abs((h % 85) - 42.5))) + m;
  c+= m;
  uint8_t r,g,b;
  switch(h_i) {
  case 0:
    r=c,g=x,b=m;
    break;
  case 1:
    r=x,g=c,b=m;
    break;
  case 2:
    r=m,g=c,b=x;
    break;
  case 3:
    r=m,g=x,b=c;
	break;
  case 4:	
    r=x,g=m,b=c;
    break;
  default:
    r=c,g=m,b=x;
	break;
  }
  return CRGB(r,g,b);*/
}


static void plot(int x, int y, float c, uint8_t display[][37])  {
	if(x < 37 && y < 37  && x >= 0 && y >= 0){
		int newVal = (int)(c*255); 
		if(display[x][y] + newVal > 255)
			display[x][y]  = 255;
		else
			display[x][y] += newVal; 
	}
}

 
static float fpart(float x) {
	return x-(float)((long)x);
}
 
static float rfpart(float x) {
     return 1 - fpart(x);
}

	
static void swap(float & x, float & y) {
	float t = x;
	x = y;
	y = t;
}
static void drawLine(float x0, float y0, float x1, float y1, uint8_t display[][37]) {
	bool steep = abs(y1-y0) > abs(x1-x0);
    if(steep) {
		swap(x0,y0);
		swap(x1,y1);
	}
    if( x0 > x1 ) {
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
     if(steep) {
         plot(ypxl1,   xpxl1, rfpart(yend) * xgap,display);
         plot(ypxl1+1, xpxl1,  fpart(yend) * xgap,display);
	 }
     else {
         plot(xpxl1, ypxl1  , rfpart(yend) * xgap,display);
         plot(xpxl1, ypxl1+1,  fpart(yend) * xgap,display);
    }
     float intery = yend + gradient; // first y-intersection for the main loop
 
     // handle second endpoint
 
     xend = round(x1);
     yend = y1 + gradient * (xend - x1);
     xgap = fpart(x1 + 0.5);
     float xpxl2 = xend; //this will be used in the main loop
     float ypxl2 = (int)yend;
     if (steep ) {
         plot(ypxl2  , xpxl2, rfpart(yend) * xgap, display);
         plot(ypxl2+1, xpxl2,  fpart(yend) * xgap, display);
	 }
     else {
         plot(xpxl2, ypxl2,  rfpart(yend) * xgap, display);
         plot(xpxl2, ypxl2+1, fpart(yend) * xgap, display);
	 }
 
     // main loop
	for(int x = xpxl1 +1; x < xpxl2; x++) {
          if(steep) {
             plot((int)intery, x, rfpart(intery),display);
             plot(((int)intery)+1, x,  fpart(intery),display);
		  }
         else {
             plot(x, (int)intery,  rfpart(intery), display);
             plot(x, ((int)intery)+1, fpart(intery), display);
		 }
         intery = intery + gradient;
	}
}
 
};

#endif