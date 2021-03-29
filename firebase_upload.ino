#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>


// Set these to run example.
// digital pin 5
#define button_pin 5
int counter=0;
bool up=true;
  
#define FIREBASE_HOST "timertracker-29904-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "DK32ztW8xJsHiDepJzHRoKIPZw0IPiCVaZ5CO8uq"
#define WIFI_SSID "Daddy's Network"
#define WIFI_PASSWORD "PhiDelt1902"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 0, NEO_GRB + NEO_KHZ800);

void setup() {
  
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  strip.begin();
  strip.show();
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
  // set button pin as an input
  pinMode(button_pin, INPUT);
}

void loop() {
  if(WiFi.status() != WL_CONNECTED)
  {
    strip.setPixelColor(0,156, 19, 9);
    strip.setBrightness(counter++);
    strip.show();
    if(counter==150)
    {
      counter=0;
    }
  }
  else
  {
    for(int i=0; i<=150; i++)
    {
      strip.setPixelColor(0,18, 127, 222);
      strip.setBrightness(i);
      strip.show();
      if(digitalRead(button_pin)==0)
      {
        sendToFirebase();
      }  
      delay(10);
    }
    for(int i=150; i>=0; i--)
    {
      strip.setPixelColor(0,18, 127, 222);
      strip.setBrightness(i);
      strip.show();
      if(digitalRead(button_pin)==0)
      {
        sendToFirebase();
      }  
      delay(10);
    }   
  }
}

void sendToFirebase()
{
  Firebase.setInt ("/Spray/Sprays",0);
  if(Firebase.failed())
  {
      strip.setPixelColor(0,156, 19, 9);
      strip.setBrightness(200);
      strip.show();
      delay(100);
      strip.setBrightness(0);
      strip.show();
      delay(50);
      strip.setPixelColor(0,156, 19, 9);
      strip.setBrightness(200);
      strip.show();
      delay(100);
      strip.setBrightness(0);
      strip.show();
    Serial.println(Firebase.error());
    return;
  }
  else
  {
    
      strip.setPixelColor(0,32, 230, 18);
      strip.setBrightness(200);
      strip.show();
      delay(100);
      strip.setBrightness(0);
      strip.show();
      delay(50);
      strip.setPixelColor(0,32, 230, 18);
      strip.setBrightness(200);
      strip.show();
      delay(100);
      strip.setBrightness(0);
      strip.show();
    return;
  }
}
