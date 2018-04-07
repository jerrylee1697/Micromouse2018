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

void setup() {
  randomSeed(0);
  blinkLEDTimer.begin(blinkLED, 500000);
  Serial1.begin(9600);
  Serial1.println("Start");

//  pinMode(BluetoothRX, INPUT);
//  pinMode(BluetoothTX, OUTPUT);
//  mySerial.begin(9600);
//  mySerial.println("Bluetooth Serial Begin");
  
  delay(2000);
  
  initializePinModes();
  attachInterrupts();

  sysTickTimer.begin(sysTick, 5000);
  readSensors();
  targetLeft = Receiver_FL_Reading;
  targetRight = Receiver_FR_Reading;
  useSensors = true;
}

elapsedMillis wait_ms2;

//int count = 1;
void loop() {
//  Serial1.println("hello!\n");
//  delay(1000);
  navigate();
//  if (wait_ms > 3000) {
//    wait_ms = 0;
//  }
//  else if (wait_ms > 2000) {
//    targetSpeedX = 0;
//  }
//  else if (wait_ms > 1500) {
//    targetSpeedX = -15;
//  }
//  else if (wait_ms > 500) {
//    targetSpeedX = 0;
//  }
//  else {
//    targetSpeedX = 15;
//  }
  /*
  moveOneCell();
  turnRight();
  moveOneCell();
  turnRight();
  moveOneCell();
  turnLeft();
  moveOneCell();
  turnLeft();
  
  moveOneCell();
  turnRight();
  moveOneCell();
  turnRight();
  moveOneCell();
  turnLeft();
  moveOneCell();
  turnLeft();
  
  moveOneCell();
  turnRight();
  turnRight();
  */
}

void sysTick() {
  readSensors();
  updateEncoderStatus();
  updateCurrentSpeed();
  PID();
}
