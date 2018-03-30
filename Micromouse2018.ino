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
  delay(2);
  
  initializePinModes();
  attachInterrupts();

  sysTickTimer.begin(sysTick, 5000);
}

elapsedMillis wait_ms2;

int count = 1;
void loop() {
//  Forward();
  while (count > 0) {
//    moveOneCell();
//    targetSpeedX = 0;
    turnLeft();
    count= count -1;
    targetSpeedW = 0;
    Serial.println("STOP");
    
  }
}

void sysTick() {
  readSensors();
  updateEncoderStatus();
  updateCurrentSpeed();
  PID();
}
