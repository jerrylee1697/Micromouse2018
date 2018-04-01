#include "inc/macros.h"
#include "inc/setup.h"
#include "inc/sensors.h"
#include "inc/delay.h"
#include "inc/led.h"
#include "inc/encoders.h"
#include "inc/pid.h"
#include "inc/pwm.h"
#include "inc/movement.h"
#include <SoftwareSerial.h>

IntervalTimer sysTickTimer;
IntervalTimer blinkLEDTimer; // So we know the Teensy is running

SoftwareSerial mySerial(BluetoothRX, BluetoothTX);

void setup() {
  blinkLEDTimer.begin(blinkLED, 500000);
//  Serial.begin(9600);
//  Serial.println("Start");

  pinMode(BluetoothRX, INPUT);
  pinMode(BluetoothTX, OUTPUT);
  mySerial.begin(9600);
  mySerial.println("Bluetooth Serial Begin");
  
  delay(2000);
  
  initializePinModes();
  attachInterrupts();

  sysTickTimer.begin(sysTick, 5000);
  readSensors();
  targetLeft = Receiver_FL_Reading;
  targetRight = Receiver_FR_Reading;
//  Serial.println(targetLeft);
//  Serial.println(targetRight);
}

elapsedMillis wait_ms2;

//int count = 1;
void loop() {
//  Serial.print("targetLeft: ");
//  Serial.println(targetLeft);
//  Serial.print("targetRight: ");
//  Serial.println(targetRight);
//  delay(20);
//  moveOneCell();
//  if (mySerial.available()) {
//    Serial.write(mySerial.read());
//  }
//  if (Serial.available()) {
//    mySerial.write(Serial.rea));
//  }
  mySerial.println("123");
//  turnLeft();
  delay(2000);
}

void sysTick() {
  readSensors();
  updateEncoderStatus();
  updateCurrentSpeed();
  PID();
}
