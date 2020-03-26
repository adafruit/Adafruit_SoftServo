// This is an ultra simple software servo driver. For best
// results, use with a timer0 interrupt to refresh() all
// your servos once every 20 milliseconds!
// Written by Limor Fried for Adafruit Industries, BSD license

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
 
#include "Adafruit_SoftServo.h"

Adafruit_SoftServo::Adafruit_SoftServo(void) {
  isAttached = false;
  servoPin = 255;
  angle = 90;
}

void Adafruit_SoftServo::attach(uint8_t pin) {
  servoPin = pin;
  angle = 90;
  isAttached = true;
  pinMode(servoPin, OUTPUT);
}

void Adafruit_SoftServo::detach(void) {
  isAttached = false;
  pinMode(servoPin, INPUT);
}

boolean  Adafruit_SoftServo::attached(void) {
  return isAttached;
}

void Adafruit_SoftServo::write(uint8_t a) {
  angle = a;

  if (! isAttached) return;
  micros = map(a, 0, 180, 1000, 2000);  
}

uint8_t Adafruit_SoftServo::read() {
  if (! isAttached) return 0;
  return angle;
}

void Adafruit_SoftServo::writeMicroseconds(uint16_t m) {
  if (! isAttached) return;
  micros = constrain(m, 0, 2000);
}

void Adafruit_SoftServo::refresh(void) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(micros);
  digitalWrite(servoPin, LOW);
}
