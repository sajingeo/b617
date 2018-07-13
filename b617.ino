/*
 * test code by sajingeo create for the Boston617 DC26 badge!!
 * This is only a test code!!
 * 
 * Credits to @TheDukeZip for the cool badge!!
 * 
 * resources :
 * 
 * board support https://cdn.sparkfun.com/assets/learn_tutorials/1/5/0/attiny-ide-1.6.x.zip
 * place the atiny folder in /Documents/Arduino/hardware
 * 
 * i2c library http://playground.arduino.cc/Code/USIi2c
 * 
 * How to program the attiny85 SOIC 
 * https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide
 * https://www.sparkfun.com/products/13153
 * 
 */

#include "TinyWireS.h"

#define EYE_LEFT_LED   (4)    // pint 3
#define EYE_RIGHT_LED  (1)   // pin 6
#define LED3           (3)
#define I2C_SLAVE_ADDR  0x99  // (617 >> 2)
// SDA- Pin 5
// SCK- Pin 7

void blink_led_three()
{
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED3, LOW);
  delay(100);
}

void blink_eye()
{
  digitalWrite(EYE_LEFT_LED, HIGH);
  digitalWrite(EYE_RIGHT_LED, HIGH);
  delay(1000);
  digitalWrite(EYE_LEFT_LED, LOW);
  digitalWrite(EYE_RIGHT_LED, LOW);
  delay(1000);
}

void blink_eye_fast()
{
  for (int i = 0; i<= 99999;i++)
  {
    digitalWrite(EYE_LEFT_LED, HIGH);
    digitalWrite(EYE_RIGHT_LED, HIGH);
    delay(100);
    digitalWrite(EYE_LEFT_LED, LOW);
    digitalWrite(EYE_RIGHT_LED, LOW);
    delay(100);
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(EYE_LEFT_LED, OUTPUT);
  pinMode(EYE_RIGHT_LED, OUTPUT);
  TinyWireS.begin(I2C_SLAVE_ADDR);
}

void loop() {
  byte byteRcvd = 0;
  // put your main code here, to run repeatedly:
  blink_eye();
  blink_led_three();
  if (TinyWireS.available()){           // got I2C input!
    byteRcvd = TinyWireS.receive();
    byteRcvd += 10;
    TinyWireS.send(byteRcvd);
    blink_eye_fast();                  
  }
}
