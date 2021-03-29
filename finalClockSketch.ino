#include <Servo.h>
#include <SoftwareSerial.h>

#define RX 0
#define TX 1
#define dirPin 12
#define stepPin 11
#define stepsPerRevolution 400
SoftwareSerial esp8266(RX,TX);

int currentSpray=0;
int currentHits=0;

int enB = 3;
int in3 = 5;
int in4 = 4;

int message;

Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  myservo.attach(9);

  //pin modes out for motor (enB for speed of motor movement)
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  //set motor to off
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  //constantly check database for new data
  if(esp8266.available())
  {
    message=esp8266.read();
    switch(message):
    case 0:
      currentHits=esp8266.read();
      break;
    case 1:
      currentSpray=esp8266.read();
      break;
    default:
      Serial.println("error");
  }

  if(currentSpray>0)
  {
    sprayPainter();
  }

  if(currentHits>0)
  {
    hammerWindUp(currentHits);
  }
  
  //if new data appears, send to appropriate function (spray paint or hammer)
  
}

void hammerWindUp(int totalHits){
  //spin motor in clockwise direction (raise hammer)
    for(int j=0; j<totalHits; j++)
    {
      //free hammer from main gear
      analogWrite(enB, 255);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      delay(150);
      //turn off motor
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);

      //engage middle gear
      digitalWrite(dirPin, LOW);
      for(int i=0; i < stepsPerRevolution*3; i++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);  
      }

      //middle gear not engaged at this point (will be caught by movement though)
      //swing hammer up
      analogWrite(enB, 255);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      delay(1550);
      //turn off motor
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enB, 255);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);      
      delay(50);
      //turn off motor
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);

      //disengage middle gear
      digitalWrite(dirPin, HIGH);
      for(int i=0; i < stepsPerRevolution*3; i++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
          
      }
    }
    //set firebase to no hits
    Serial.write(0);
}

void sprayPainter(){
  
  //start sprayer
  for(int i=90; i>10; i=i-10)
  {
    myservo.write(i);
    delay(100);
  }

  //run gear around clock (keeping hammer out of path)
  analogWrite(enB, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(4000);

  //stop sprayer
  myservo.write(90);

  //set firebase to no sprays
  Serial.write(1);
}
