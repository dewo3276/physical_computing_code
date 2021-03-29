#include <Servo.h>

#define dirPin 12
#define stepPin 11
#define stepsPerRevolution 400

int currentSpray=0;
int currentHits=0;

int incoming=0;

int enB = 3;
int in3 = 5;
int in4 = 4;

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
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0)
  {
  incoming=Serial.read();
    Serial.println(incoming);
  }
  if(incoming==51)
  {
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
  /*
    //disengage middle gear
    digitalWrite(dirPin, HIGH);
    for(int k=0; k<4; k++)
    {
      for(int i=0; i < stepsPerRevolution; i++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);  
      }
    }
    delay(5000);
  
    //spin motor in counter-clockwise direction
    analogWrite(enB, 255);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(500);
    //turn off motor
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  
    //re-engage middle gear
    digitalWrite(dirPin, LOW);
    for(int k=0; k<4; k++)
    {
      for(int i=0; i < stepsPerRevolution; i++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);  
      }
    }
    */
    incoming=0;
  }

  if(incoming==52)
  {
    analogWrite(enB, 255);
    digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
      
    delay(150);
    //turn off motor
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
  incoming=0;
  }

if(incoming==53)
{
   digitalWrite(dirPin, HIGH);
      for(int i=0; i < stepsPerRevolution*3; i++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
/*
        analogWrite(enB, 255);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);

        delay(10);
        
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);

        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);

        delay(10);
        
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        */
    }
    incoming=0;
}

if(incoming==54)
{
 digitalWrite(dirPin, LOW);
      for(int i=0; i < stepsPerRevolution*1.5; i++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);  
}

      incoming=0; 
}
if(incoming==55)
{
 digitalWrite(dirPin, HIGH);
      for(int i=0; i < stepsPerRevolution*.5; i++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);  
}

      incoming=0; 
}

}
