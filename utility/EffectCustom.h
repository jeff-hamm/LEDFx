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

#ifndef INC_CUSTOMEFFECT_H
#define INC_CUSTOMEFFECT_H
#include "Effect.h"

typedef void(*RenderFrameFunc)(unsigned int, const LEDStripSection&);
// An effect with a callback to a custom user display function
class EffectCustom : public LEDEffect {
private:
	RenderFrameFunc renderFrameFunc;
public :
	EffectCustom(RenderFrameFunc renderFrameFunc) {
		this->renderFrameFunc = renderFrameFunc;
	}

	void renderFrame(uint16_t currentFrame, const LEDStripSection & context) {
		if (renderFrameFunc)
			return renderFrameFunc(currentFrame, context);
	}
};

#endif