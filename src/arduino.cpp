#include <SoftwareSerial.h>
#include "AFMotor.h"
#include <Arduino.h>

#define Speed 180

#define rxPin A2   // RX, TX pins for SoftwareSerial
#define txPin A3

#define yellow_left A1
#define yellow_right A0
#define white A4
#define red A5

AF_DCMotor motor1(3);
AF_DCMotor motor2(4);

SoftwareSerial mySerial(rxPin, txPin); 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); 
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  pinMode(yellow_left, OUTPUT);
  pinMode(yellow_right, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(red, OUTPUT);
  digitalWrite(white, HIGH );
}

void loop() {
  if (mySerial.available()) {
    char data = mySerial.read();
    Serial.write(data);
    if (data == '3')  {                // LEFT = 3
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      digitalWrite(red, LOW);
      digitalWrite(yellow_left, HIGH);
      digitalWrite(yellow_right, LOW);
      digitalWrite(white, HIGH );
    } else if (data == '4') {           // RIGHT = 4
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      digitalWrite(red, LOW);
      digitalWrite(yellow_left, LOW);
      digitalWrite(yellow_right, HIGH);
      digitalWrite(white, HIGH );
    } else if (data == '1') {           // FORWARD = 1
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      digitalWrite(red, LOW);
      digitalWrite(yellow_left, LOW);
      digitalWrite(yellow_right, LOW);
      digitalWrite(white, HIGH );
    } else if (data == '2') {         // BACKWARD = 2
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      digitalWrite(red, HIGH);
      digitalWrite(yellow_left, LOW);
      digitalWrite(yellow_right, LOW);
      digitalWrite(white, HIGH );
    } else if (data == '0') {          // STOP = 0
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      digitalWrite(red, LOW);
      digitalWrite(yellow_left, LOW);
      digitalWrite(yellow_right, LOW);
      digitalWrite(white, HIGH );
    }  else if (data == '5') {          // LIGHTS OFF = 5
      digitalWrite(red, LOW);
      digitalWrite(yellow_left, LOW);
      digitalWrite(yellow_right, LOW);
      digitalWrite(white, LOW );
    }
    mySerial.write(data);
  }
}