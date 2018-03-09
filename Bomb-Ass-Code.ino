#include "inc/macros.h"
#include "inc/setup.h"
#include "inc/sensors.h"
#include "inc/delay.h"
#include "inc/led.h"
#include "inc/encoders.h"
#include "inc/pid.h"
#include "inc/pwm.h"
#include "inc/motors.h"

IntervalTimer sysTickTimer;
IntervalTimer blinkLEDTimer; // So we know the Teensy is running
IntervalTimer TurnRight;
IntervalTimer resetEncoders;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  
  initializePinModes();
  attachInterrupts();

  sysTickTimer.begin(sysTick, 5000);
  blinkLEDTimer.begin(blinkLED, 500000);
//  TurnRight.begin(RightTurn, 2500000);
//  resetEncoders.begin(ResetEncoders, 10000);
}

void loop() {
  if (wait_ms > 100) {
    printSensors();
    printEncoders();
    wait_ms = 0;
    if (encoderValueLeft % 1000 == 0) {
      RightTurn();
      ResetEncoders();
    }
    else {
      Forward();
    }
  }
}

void sysTick() {
  readSensors();
  updateEncoderStatus();
//  PID();
}
