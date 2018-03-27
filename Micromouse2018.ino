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

void loop() {
  targetSpeedW = 0;
  targetSpeedX = moveSpeed;
  distanceLeftX = 900;
  elapsedMillis wait;
//  do {
//    /*you can call int needToDecelerate(int32_t dist, int16_t curSpd, int16_t endSpd)
//    here with current speed and distanceLeft to decide if you should start to decelerate or not.*/
//    if(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed) < decX)
//      targetSpeedX = maxSpeed;
//    else
//      targetSpeedX = moveSpeed;
//    if (wait > 5) {
//      Serial.println(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed));
//      // Serial.println(encoderCount-oldEncoderCount);
//      wait = 0;
//    }
//    //there is something else you can add here. Such as detecting falling edge of post to correct longitudinal position of mouse when running in a straight path
//  }
//  while( (encoderCountX-oldEncoderCount) < 900);
  //LFvalues1 and RFvalues1 are the front wall sensor threshold when the center of mouse between the boundary of the cells.
  //LFvalues2 and RFvalues2 are the front wall sensor threshold when the center of the mouse staying half cell farther than LFvalues1 and 2
  //and LF/RFvalues2 are usually the threshold to determine if there is a front wall or not. You should probably move this 10mm closer to front wall when collecting
  //these thresholds just in case the readings are too weak.
  delay(1000);
  oldEncoderCount = encoderCountX;

  
//  distanceLeftW = 235;//97
//  do {
//     /*you can call int needToDecelerate(int32_t dist, int16_t curSpd, int16_t endSpd)
//    here with current speed and distanceLeft to decide if you should start to decelerate or not.*/
//    if(needToDecelerate(distanceLeftW, encoderFeedbackW, 0) < decW)
//      targetSpeedW = turnSpeed;
//    else
//      targetSpeedW = 0;
//    if (wait_ms2 > 3) {
//      Serial.print(needToDecelerate(distanceLeftW, encoderFeedbackW, 0));
//      Serial.print(',');
//      Serial.println(distanceLeftW);
//      wait_ms2 = 0;
//    }
//    //there is something else you can add here. Such as detecting falling edge of post to correct longitudinal position of mouse when running in a straight path
//  }
//  while( (encoderCountW-oldEncoderCount) < 250);
////  targetSpeedW = 0;
//  delay(1000);
//  oldEncoderCount = encoderCountW;

//  if (wait_ms > 6000) {
//    wait_ms = 0;
//  }
//  else if (wait_ms > 4500) {
//    targetSpeedW = -70;
//  }
//  else if (wait_ms > 3000) {
//    targetSpeedW = 0;
//  }
//  else if (wait_ms > 1500) {
//    targetSpeedW = 70;
//  }
//  else {
//    targetSpeedW = 0;
//  }
//  
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
  PID();
}
