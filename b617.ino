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
 * I2C Lib : https://github.com/lucullusTheOnly/TinyWire
 * 
 * How to program the attiny85 SOIC 
 * https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide
 * https://www.sparkfun.com/products/13153
 * 
 * Version 1.2
 * 
 */
//#include "TinyWireS.h"
#include <TinyWire.h>

#define EYE_LEFT_LED   (3)    // pint 3
#define EYE_RIGHT_LED  (4)   // pin 6
#define LED3           (1)
#define I2C_SLAVE_ADDR  0x26 
// SDA- Pin 5
// SCK- Pin 7

bool we_heard_our_address = false;

char data_to_send[] = "Ya badge’s wicked pissa";

void blink_led_three()
{
  digitalWrite(LED3, HIGH);
  delay(500);
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

void blink_eye_fast(uint8_t val)
{
  for (int i = 0; i<= val;i++)
  {
    digitalWrite(EYE_LEFT_LED, HIGH);
    digitalWrite(EYE_RIGHT_LED, HIGH);
    delay(200);
    digitalWrite(EYE_LEFT_LED, LOW);
    digitalWrite(EYE_RIGHT_LED, LOW);
    delay(200);
  }
}


void setup() {
  // put your setup code here, to run once:
  noInterrupts(); // since INT0 is attached to pin 7
  
  pinMode(EYE_LEFT_LED, OUTPUT);
  pinMode(EYE_RIGHT_LED, OUTPUT);
  pinMode(LED3, OUTPUT);
//  TinyWireS.begin(I2C_SLAVE_ADDR);
  TinyWire.begin( I2C_SLAVE_ADDR );
  TinyWire.onRequest( onI2CRequest );
  TinyWire.onReceive( onI2CReceive );
}

void loop() {
  interrupts();
  byte byteRcvd = 0;
  blink_eye();
  blink_led_three();
  if(we_heard_our_address)
  {
    we_heard_our_address = false;
    blink_eye_fast(10);
  }
}

void onI2CRequest() {
  for(int i=0; i<= 23 ;i++)
  {
     TinyWire.send(data_to_send[i]);
  }
}

void onI2CReceive(int howMany){
  // loops, until all received bytes are read
  while(TinyWire.available()>0){
    TinyWire.read();
    we_heard_our_address = true;
  }
  }


