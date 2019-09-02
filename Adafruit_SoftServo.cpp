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
  rangeLo = 1000;
  rangeHi = 2000;
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
  micros = map(a, 0, 180, rangeLo, rangeHi);
}

void Adafruit_SoftServo::refresh(void) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(micros);
  digitalWrite(servoPin, LOW);
}

void Adafruit_SoftServo::setRangeMin(uint16_t lo)
{
  rangeLo = constrain(lo, 256, 3000);
}

void Adafruit_SoftServo::setRangeMax(uint16_t hi)
{
  rangeHi = constrain(hi, 256, 3000);
}
