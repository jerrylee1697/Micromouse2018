#include "inc/macros.h"
#include "inc/setup.h"
#include "inc/sensors.h"
#include "inc/delay.h"
#include "inc/led.h"
#include "inc/encoders.h"
#include "inc/pid.h"
#include "inc/pwm.h"
#include "inc/movement.h"

IntervalTimer sysTickTimer;
IntervalTimer blinkLEDTimer; // So we know the Teensy is running

void setup() {
  blinkLEDTimer.begin(blinkLED, 500000);
  Serial.begin(9600);
  Serial.println("Start");
  delay(1000);
  
  initializePinModes();
  attachInterrupts();

  sysTickTimer.begin(sysTick, 5000);
//  targetLeft = Receiver_FL_Reading;
//  targetRight = Receiver_FR_Reading;
}

elapsedMillis wait_ms2;

//int count = 2;
void loop() {
  moveOneCell();
  turnLeft();
}

void sysTick() {
  readSensors();
  updateEncoderStatus();
  updateCurrentSpeed();
  PID();
}
