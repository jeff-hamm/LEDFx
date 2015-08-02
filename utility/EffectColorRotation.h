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

#ifndef INC_EFFECTCOLORROTATION_H
#define INC_EFFECTCOLORROTATION_H
#include "Effect.h"

// A simple effect that rotates through randomly chosen hues which match the saturation and value of ReferenceColor1
class EffectColorRotation : public LEDEffect
{
private:
  CRGB currentColor;
  CRGB nextColor;
  uint16_t frameDuration;
  uint16_t fadeDuration;
  uint16_t lastChange;
  CRGB getNextColor(const LEDStripSection & context);
  void updateRotation(uint16_t currentFrame, const LEDStripSection & context);
public:
  // Create a solid color effect from the saturation and value of ReferenceColor1
  // colorDuration controls how many frames each color is held statically. 
  // FadeDuration controls how many frames are used to transition from 1 color to the next
  EffectColorRotation(uint16_t colorDuration = 0, uint16_t fadeDuration = 300);
  // copy constructor
  EffectColorRotation(EffectColorRotation&);
  // called once per frame. Useful for cashing frame-level values.
  virtual void renderFrame(uint16_t currentFrame,const LEDStripSection & context, CRGB * ledBuffer);
  void reset();
};

#endif