
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 4
#define LEDcount 2

#include <Servo.h>

Servo servR,servL;

Adafruit_NeoPixel strip=Adafruit_NeoPixel(LEDcount,PIN,NEO_GRB+NEO_KHZ800);

int bend=0;
int pot=0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  servR.attach(10);
  servL.attach(11);
}

void loop() {
  
  bend=analogRead(A0);
  pot=analogRead(A1);
  

  int brightPot=map(pot,1023,0,0,100);
  int moveBend=map(bend,140,352,0,100);
  int colorBendRed=map(bend,120,352,10,250);
  int colorBendBlue=map(bend,120,352,250,10);


  strip.setPixelColor(0,colorBendRed,0,colorBendBlue);
  strip.setPixelColor(1,colorBendRed,0,colorBendBlue);
  strip.setBrightness(brightPot);
  strip.show();
  
  servR.write(moveBend);
  moveBend=map(moveBend,0,100,100,0);
  servL.write(moveBend);
  delay(15);
}
