#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "timertracker-29904-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "DK32ztW8xJsHiDepJzHRoKIPZw0IPiCVaZ5CO8uq"
#define WIFI_SSID "Bills Network"
#define WIFI_PASSWORD "jbthsv0622"

int message;
int currentSpray;
int currentHits;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    message=Serial.read();      
    switch(message)
    {
      case 0:
        Firebase.setInt("userTimes/Hits",0);
        break;
      case 1:
        Firebase.setInt("Spray/Sprays",0);
        break;
      default: 
        Serial.println("error");
        break;
    }
  }
  currentSpray=Firebase.getInt("Spray/Sprays");
  currentHits=Firebase.getInt("userTimes/Hits");
  if(currentSpray>0)
  {
    Serial.write(1);
    Serial.write(currentSpray);
  }
  if(currentHits>0)
  {
    Serial.write(0);
    Serial.write(currentHits);
  }
}
