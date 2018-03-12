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

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  delay(1);
  
  initializePinModes();
  attachInterrupts();

  sysTickTimer.begin(sysTick, 5000);
  blinkLEDTimer.begin(blinkLED, 500000);
}

double i = 0;
int flag = 0;
elapsedMillis wait_ms2;

void loop() {
  if (wait_ms > 2000) {
    wait_ms = 0;
  }
  if (wait_ms > 1200) {
    targetSpeedX = 0;
  }
  else if (wait_ms > 1000) {
    targetSpeedX = 70;
  }
  else if (wait_ms > 500) {
    targetSpeedX = 0;
  }
  else {
//    targetSpeedX = -60;
  }

//  //Figure 8
//  targetSpeedX = 15;
//  if (wait_ms > 2400) {
//    wait_ms = 0;
//  }
//  else if (wait_ms > 1900) {
//    targetSpeedW = 0;
//  }
//  else if (wait_ms > 1200) {
//    targetSpeedW = 12;
//  }
//  else if (wait_ms > 700) {
//    targetSpeedW = 0;
//  }
//  else {
//    targetSpeedW = -12;
//  }
//  if(wait_ms > 2750) {
//    delay(100000);
//    wait_ms = 0;
//  }
//  else if(wait_ms > 2000) {
//    targetSpeedX = 0;
//  }
//  else if(wait_ms > 1000) {
//    targetSpeedX = 100;
//  }
  
//  if (flag == 0 && wait_ms > 10) {
//    i += 1;
//    wait_ms = 0;
//    if (i > 35) {
//      flag = 1;
//    }
//  }
//  else if (flag == 1 && wait_ms > 10) {
//    i -= 1;
//    wait_ms = 0;
//    if (i < -35) {
//      flag = 0;
//    }
//  }
  if (wait_ms2 > 20) {
    Serial.print(posErrorX);
    Serial.print(",");
    Serial.println(posPwmX);
    wait_ms2 = 0;
  }
  
//  //Figure 8 for loop
//  targetSpeedX = 15;
//  for (double i = 0; i < 15; i += 0.2) {
//    delayMicroseconds(5000);
//    targetSpeedW = i;
//  }
//  for (double i = 15; i > 0; i -= 0.2) {
//    delayMicroseconds(5000);
//    targetSpeedW = i;
//  }
//  for (double i = 0; i < 15; i += 0.2) {
//    delayMicroseconds(5000);
//    targetSpeedW = -i;
//  }
//  for (double i = 15; i > 0; i -= 0.2) {
//    delayMicroseconds(5000);
//    targetSpeedW = -i;
//  }
  /*
  if (wait_ms > 1000) {
    printSensorsAmbient();
    printSensorsRaw();
    printSensors();
    printEncoders();
    
    wait_ms = 0;
  }
  */
  
}

void sysTick() {
  readSensors();
  updateEncoderStatus();
  updateCurrentSpeed();
  calculateMotorPwm();
}
