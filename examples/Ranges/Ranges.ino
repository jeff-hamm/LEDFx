#include "FastSPI_LED2.h"
#define LEDLIB_GRB_ORDER
#include "LEDFx.h"

#define NUM_LEDS 128
#define LED_PIN 8
LEDFxLib LEDFx(NUM_LEDS);
WS2811Controller800Mhz<LED_PIN> fastSPI;

#define TOP_SIZE 6
#define MID_SIZE 13
#define BOTTOM_SIZE 9*3
#define BOTTOM_ORIGIN TOP_SIZE*2+MID_SIZE*2
#define NUM_LOCATIONS 6
RGB buffer[NUM_LEDS];
enum Locations
{
	// 0b000001
	TopOut = 0x01,
	// 0b000010
	TopIn = 0x02,
	// 0b000100
	MidOut = 0x04,
	// 0b001000
	MidIn = 0x08,
	// 0b010000
	BotOut = 0x10,
	// 0b100000
	BotIn = 0x20
};

enum Mode { Solid = 0x01, Sin = 0x02 };

EffectSolidColor solidEffect;
// sin wave from white to blue. 
EffectSineWave sin1(cRGB(255,255,255),cRGB(0,0,255), 2);

void setup()
{
	Serial.begin(115200);


	// setup the light strip. 
	fastSPI.init();
	fastSPI.showRGB((byte*)buffer, NUM_LEDS);

	// initialize the LED library.
	LEDFx.init(buffer);

	// slow the sin wave down a bit. set the framerate here
	sin1.setFramerate(30, FRAME_ORDER_SEQUENTIAL);

	// top triangle outer
	LEDFx.addRange(TopOut, 0,TOP_SIZE);
	// top triangle inner
	LEDFx.addRange(TopIn, TOP_SIZE,TOP_SIZE);
	// mid triangle outer
	LEDFx.addRange(MidOut, 2*TOP_SIZE,MID_SIZE);
	// mid triangle inner
	LEDFx.addRange(MidIn, 2*TOP_SIZE+MID_SIZE,MID_SIZE);
	// bottom triangle outer
	LEDFx.addRange(BotOut, BOTTOM_ORIGIN, BOTTOM_SIZE);
	// bottom triangle inner
	LEDFx.addRange(BotIn, BOTTOM_ORIGIN + BOTTOM_SIZE,BOTTOM_SIZE);
}

void loop()
{
	updateData();

	if(LEDFx.update())
		fastSPI.showRGB((byte*)buffer, NUM_LEDS);
}

void updateData() {
	if(shouldChangeRange()) {
		byte data[3];
		getData(data);
		Mode m = (Mode)data[0];
		int location = data[1];
		int param1 = data[2];
		switch(m) {
		case Solid:
			setSolidColor(location, param1);
			break;
		case Sin:
			setSin(location, param1);
			break;
		}
	}
}

unsigned int lastChange = 0;
bool shouldChangeRange() {
	if(millis() - lastChange > 1000)  {
		lastChange = millis();
		return true;
	}
	else
		return false;
}

void getData(byte * data) {
	data[0] = random(1,3);
	data[1] = 0x01 << random(0,6);
	data[2] = random(0,255);
}
void setSolidColor(int locations, byte param) {
	int count = 0;
	while(count < NUM_LOCATIONS) {
		if((locations >> count) & 0x01) {
			LEDFx.setCurrentEffectWithArgs(solidEffect, 0x01 << count,LEDFxUtilities::HSVtoRGB(param,255,200));
		}
		count++;
	}
}

void setSin(int locations, byte param) {
	int count = 0;
	while(count < NUM_LOCATIONS) {
		if((locations >> count) & 0x01) {
			LEDFx.setCurrentEffectWithArgs(sin1, 0x01 << count,
				LEDFxUtilities::HSVtoRGB(param,255,255),
				cRGB(0,0,0),
				2);
		}
		count++;
	}
}

void setEffectLocations(LEDEffect & eff, int locations)  {
	int count = 0;
	while(count < NUM_LOCATIONS) {
		if((locations >> count) & 0x01) {
			LEDFx.setCurrentEffect(eff, 0x01 << count);
		}
		count++;
	}
}