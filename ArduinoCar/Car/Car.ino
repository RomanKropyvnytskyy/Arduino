#include <Servo.h>

Servo myservo; 

const int trigPin = 3;
const int echoPin = 2;
const int servoPin = 9;

//int enA = 9;
int in1 = 4;
int in2 = 5;

//int enB = 3;
int in3 = 6;
int in4 = 7;

void setup() {

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //pinMode(enA, OUTPUT);
  //pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(servoPin,OUTPUT);
  myservo.attach(servoPin); 

  myservo.write(70);
  delay(1000);

}

void loop() {

  long leftdistance, rightdistance, distance;

  distance = measuringDistance();

  if (distance <= 30) {
    totalstop();

    myservo.write(20);
    delay(1000);
    leftdistance = measuringDistance();

    totalstop();
    
    myservo.write(120);
    delay(1000);
    rightdistance = measuringDistance();

    totalstop();

    if ((leftdistance > 30)&&(rightdistance > 30)){
      if (leftdistance>rightdistance){
        turnleft();
      }
      else {
        turnright();  
      }  
    }
    else if (leftdistance > 30) {
      turnleft();
    }
    else if (rightdistance > 30) {
      turnright();  
    }
    else {
      moveback();
    }
  }
  else if (distance <=15) {
    totalstop();
    moveback();
  }
  else {
    moveahead();  
  }  
    
   delay(200);

}

long measuringDistance() {
  long duration;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  return duration/58;
}

void moveahead() {
  //analogWrite(enA, 100);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  //analogWrite(enB, 100);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  //delay(1000);
  
}

void moveback() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //analogWrite(enA, 100);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //analogWrite(enB, 100);

  //delay(1000);
  
}

void turnleft() {

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //analogWrite(enA, 200);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //analogWrite(enB, 200);

  delay(200);
  totalstop();
}

void turnright() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //analogWrite(enA, 200);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //analogWrite(enB, 200);

  delay(200);
  totalstop();
}

void totalstop() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  myservo.write(70);
  //delay(1000);
}

