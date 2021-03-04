
/*
  l298
  enA 5
  in1 6
  in2 7
  enb 8
  in3 9
  in4 10

  ultrasonic
  echo 3
  trig 4

  servo
  pwm = 2

*/

#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN 3
#define ECHO_PIN 4
#define MAX_DISTANCE 200
#define MAX_SPEED 128 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo;

// motor one
int enA = 5;
int in1 = 6;
int in2 = 7;
// motor two
int enB = 8;
int in3 = 9;
int in4 = 10;

#define servopin 2

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
 Serial.begin(9600);
  Serial.print("start");
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  myservo.attach(servopin);
  myservo.write(100);
  delay(2000);
  distance = readPing();
  
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);
  
   Serial.println(distance);
  if (distance <= 30)
  {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL)
    {
      turnRight();
      moveStop();
    } else
    {
      turnLeft();
      moveStop();
    }
  } else
  {
    moveForward();
  }
  distance = readPing();
}

int lookRight()
{
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(100);
  return distance;
}

int lookLeft()
{
  myservo.write(150);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(100);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  Serial.println("Stopping");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

void moveForward() {

  if (!goesForward)
  {
    goesForward = true;
    Serial.println("Going Forward");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
    {
      analogWrite(enA , speedSet);
      analogWrite(enB, speedSet + MAX_SPEED_OFFSET);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  Serial.println("Going Forward");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    analogWrite(enA , speedSet);
    analogWrite(enB, speedSet + MAX_SPEED_OFFSET);
    delay(5);
  }
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(300);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(300);
  Serial.println("Going Forward");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
