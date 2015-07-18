// LEDEffect.h
//

#ifndef INC_LEDEffect_h
#define INC_LEDEffect_h
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif
#include "Pixel.h"
#include "IDrawable.h"
#include "RangeInfoList.h"

typedef unsigned int duration_type;
typedef unsigned int frame_order;
#define DURATION_TIME 0
#define DURATION_FRAMES 1
#define FRAME_ORDER_TIME 0
#define FRAME_ORDER_SEQUENTIAL 1

#define ARG_TO(b,a,t) {memcpy(b,&a,sizeof(t));}
#define ARG_FROM(b,t) (*(t*)((b+=sizeof(t))-sizeof(t)))


class LEDEffectSequence;

// A class encapsulating a specific LED display effect. 
class LEDEffect : public IDrawable
{
protected:
  RangeInfoList * context;

public:
  // the current frame number
  uint16_t currentFrame;
  // the minimum frame wait time
  uint16_t waitTime;
  // the frame processing order of this effect
  frame_order frameOrder;
  LEDEffect();
  // initialze the effect. 
  // framesPerSecond is the number of frames desired per second
  // If the frame order is FRAME_ORDER_TIME  the effect will tick in real time 
  //      (e.g. if the wait duration is 100ms, and the processor is only able to keep up with a 5fps framerate, it will step twice for each tick)
  // if ticktype is FRAME_ORDER_SEQUENTIAL, then duration is the total frame count and the effect will complete all frames sequentially independant of processor speed
  virtual void setFramerate(float framesPerSecond, frame_order frameOrder = FRAME_ORDER_SEQUENTIAL);
  virtual void reset ();
  // called once per frame. Useful for cashing frame-level values.
  virtual void setFrame (uint16_t currentFrame, RangeInfoList * context);
  void cloneTo (LEDEffect * clone);
  // returns the effect for the current frame number at the specified pixel
  virtual void drawFrame (uint16_t currentFrame, RangeInfoList * context, CRGB * frameBuffer)  {};
  bool update(uint32_t runTime, CRGB* buffer, RangeInfoList * context);
  virtual void setArgs(char* args) = 0;
  virtual void serialize(char * buffer, int size) = 0;

};
#endif
