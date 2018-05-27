#include "inc/macros.h"
#include "inc/setup.h"
#include "inc/sensors.h"
#include "inc/delay.h"
#include "inc/led.h"
#include "inc/encoders.h"
#include "inc/pid.h"
#include "inc/pwm.h"
#include "inc/movement.h"
#include "inc/state.h"
#include "inc/floodfill.h"

IntervalTimer sysTickTimer;
IntervalTimer blinkLEDTimer; // So we know the Teensy is running

bool rightHand = false;

void setup() {
  randomSeed(0);
  initializePinModes();
  attachInterrupts();
  blinkLEDTimer.begin(blinkLED, 500000);
  Serial.begin(9600);
  Serial.println("Start");

  useSensors = false;
  sysTickTimer.begin(sysTick, 5000);

  delay(1000);
  while (1) {
    Serial.print(Receiver_L_Reading);
    Serial.print(",");
    Serial.println(Receiver_R_Reading);
    
    if (Receiver_L_Reading > 600) { // Floodfill
      break;
    }
    if (Receiver_R_Reading > 600) { // Right Hand rule
      rightHand = true;
      break;
    }
    delay(40);
  }
  delay(1000);
  readSensors();
  targetLeft = Receiver_FL_Reading;
  targetRight = Receiver_FR_Reading;
  useSensors = true;
}

void loop() {
  Serial.print(Receiver_L_Reading);
  Serial.print(",");
  Serial.println(Receiver_R_Reading);
  if (rightHand)
    navigate();
  else
    floodfill_algorithm();
}

void sysTick() {
  readSensors();
  updateEncoderStatus();
  updateCurrentSpeed();
  PID();
}
