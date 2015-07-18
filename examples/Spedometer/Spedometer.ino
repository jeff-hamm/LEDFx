#include "FastSPI_LED2.h"
#include "SPI.h"
#define LEDLIB_GRB_ORDER  1       // GRB leds
#include "LEDFx.h"

const int LED_COUNT = 128;
const int REEDPIN = 2;
const int LED_PIN1 = 8;
WS2811Controller800Mhz<LED_PIN1> fastSpi;
LEDFxLib ledFx(LED_COUNT);
RGB buffer[LED_COUNT];
EffectProgressBar progress(cRGB(0,255,0),cRGB(255,0,0));
EffectSolidColor color(cRGB(0,0,255));

const float DIAMETER_INCH = 7.87402;
const int STOP_DURATION = 3000;
// 70.4iph is 5mph
const int MIN_SPEED = 10.0;
const int MAX_SPEED = 70.4;
const float GRADIENT_STEP_SIZE = (128.0*2.0)/(float)LED_COUNT;
static float circumference;


void setup() {
  Serial.begin(9600);
  circumference = 2.0 * PI * (DIAMETER_INCH/2.0);
  pinMode(REEDPIN, INPUT_PULLUP);
  fastSpi.init();
  ledFx.init(buffer);
  ledFx.setCurrentEffect(progress);
}

  static unsigned long lastTick = millis();
  static boolean rotated = false;
  static float velocity = 0.0;
	static int lightNum = 0;
void loop() {
  if(digitalRead(REEDPIN) == HIGH) {
    rotated = true;
    if(millis() - lastTick > STOP_DURATION && velocity != 0.0) {
      velocity = 0.0;
      progress.setValue(0);
    }
  }
  // ensure that the wheel has rotated since the last velocity update.
  else if(rotated) {
    unsigned long thisTick = millis();
    unsigned long tDelta = thisTick - lastTick;
    // in inches/sec
    velocity = DIAMETER_INCH * (1000.0/(float)tDelta);
    
    lastTick = thisTick;
    rotated = false;
	  uint8_t lightNum = map(cV, MIN_SPEED,MAX_SPEED,0,255);
	  progress.setValue(lightNum);
  }

  if(ledFx.update())
	  fastSpi.showRGB((byte*)buffer, LED_COUNT);
}





