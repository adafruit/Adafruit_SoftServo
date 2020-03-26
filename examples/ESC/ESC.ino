/*******************************************************************
  SoftServo sketch for Adafruit Trinket.  Turn the potentiometer knob
  to set the speed rotation of the motor connected to the ESC (Electronic speed control)
  (0 = min speed, full = max speed)
 
  Required library is the Adafruit_SoftServo library
  available at https://github.com/adafruit/Adafruit_SoftServo
  The standard Arduino IDE servo library will not work with 8 bit
  AVR microcontrollers like Trinket and Gemma due to differences
  in available timer hardware and programming. We simply refresh
  by piggy-backing on the timer0 millis() counter
 
  Required hardware includes an Adafruit Trinket microcontroller
  a ESC connected to a brushless motor and a potentiometer (nominally 1Kohm to 100Kohm
 
  As written, this is specifically for the Trinket although it should
  be Gemma or other boards (Arduino Uno, etc.) with proper pin mappings
 
  Trinket:        USB+   Gnd   Pin #0   Pin #2 A1
  Connection:     Servo+  -    ESC   Potentiometer wiper
 
 *******************************************************************/


#include <Adafruit_SoftServo.h>


#define POT 1 // pin 2
#define MOTOR 0 // pin 0

int potValue = 0;
int motorSpeed = 0;

Adafruit_SoftServo esc;  

// the setup routine runs once when you press reset:
void setup() {  
  // Set up the interrupt that will refresh the servo for us automagically
  OCR0A = 0xAF;            // any number is OK
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)
  
  esc.attach(MOTOR);
  esc.writeMicroseconds(900); // this is required to ARM the motor, you must give an impulse less then 1000us 
  delay(4000);
}

// the loop routine runs over and over again forever:
void loop() {
  potValue = analogRead(POT); // From 0 to 1023
  motorSpeed = map(potValue, 0, 1023, 0, 180);
  esc.write(motorSpeed); // 0 to 180 motor speed
  delay(15);
}

// We'll take advantage of the built in millis() timer that goes off
// to keep track of time, and refresh the servo every 20 milliseconds
volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    esc.refresh();
  }
}