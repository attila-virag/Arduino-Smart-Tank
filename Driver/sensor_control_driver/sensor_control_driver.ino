#include <Servo.h> 

int ServoPin = 3;
Servo myservo; 

int LED_R = 11;     
int LED_G = 10;     
int LED_B = 9;     

int EchoPin = 12;             
int TrigPin = 13;       

int LEFT_REVERSE  = 7; 
int LEFT_FORWARD = 8;
int LEFT_SPEED = 6;

int RIGHT_FORWARD = 2;
int RIGHT_REVERSE = 4;
int RIGHT_SPEED = 5;

const double SPEED_OF_SOUND = 0.0343; // cm per microsecond
const int c_scanMin = 55; // regular scan min range
const int c_scanMax = 125; // regular scan max range
const int c_maxDistance = 40; // blue light max distance
const int c_stopDistance = 25; // red light/stop distance
const int c_vehicleTurnRate = 20; // this parameter controls how long we turn in relation to servo angle
const int c_motor_speed = 70; // speed of the motors is constant

long servoPosition = 90; // initialize to center

bool turningRight = true; // will flip flop this for left/right direction servo scans

bool deepScan = false; // we are in simple scan by default, deep scan does the whole range

bool manualControl = false;

void TurnHead() {
    int scanMin = c_scanMin;
    int scanMax = c_scanMax;
  if(deepScan) {
    scanMin = 5;
    scanMax = 175;
  }


  if(servoPosition < scanMin) {
    turningRight = false;
  }
  else if(servoPosition > scanMax) {
    turningRight = true;
  }
for(int i = 0; i<10; i++){
  if(turningRight) {
    servoPosition = servoPosition - 1;
   }
   else {
    servoPosition = servoPosition + 1;
   }

   if(servoPosition < 0) {
      servoPosition = 0;
    }
    if(servoPosition > 180) {
      servoPosition = 180;
    }
    
}
   myservo.write(servoPosition);
   delay(20);
}

long GetDistance(int echoPin, int trigPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (double)duration * SPEED_OF_SOUND / 2.0; 
  Serial.println("Distance: " + String(distance));
  return distance;
}

long TurnHeadAndGetDistance() {
  TurnHead();
  return GetDistance(EchoPin, TrigPin);
}

void DriveForward(int duration) {
  digitalWrite(RIGHT_FORWARD, HIGH);  
  digitalWrite(RIGHT_REVERSE ,LOW); 
  digitalWrite(LEFT_FORWARD, HIGH);  
  digitalWrite(LEFT_REVERSE , LOW); 
  analogWrite(RIGHT_SPEED, c_motor_speed);
  analogWrite(LEFT_SPEED, c_motor_speed);
  if(duration > 0){
    delay(duration);
  }
}

void Reverse(int duration) {
  digitalWrite(RIGHT_FORWARD, LOW);  
  digitalWrite(RIGHT_REVERSE ,HIGH); 
  digitalWrite(LEFT_FORWARD, LOW);  
  digitalWrite(LEFT_REVERSE , HIGH); 
  analogWrite(RIGHT_SPEED, c_motor_speed);
  analogWrite(LEFT_SPEED, c_motor_speed);
  if(duration > 0){
    delay(duration);
  }
}


void SpinRight(int duration) {
  digitalWrite(RIGHT_FORWARD, LOW);  
  digitalWrite(RIGHT_REVERSE ,HIGH); 
  digitalWrite(LEFT_FORWARD, HIGH);  
  digitalWrite(LEFT_REVERSE , LOW); 
  analogWrite(RIGHT_SPEED, c_motor_speed);
  analogWrite(LEFT_SPEED, c_motor_speed);
  if(duration > 0){
    delay(duration);
  }
}


void SpinLeft(int duration) {
  digitalWrite(RIGHT_FORWARD, HIGH);  
  digitalWrite(RIGHT_REVERSE ,LOW); 
  digitalWrite(LEFT_FORWARD, LOW);  
  digitalWrite(LEFT_REVERSE , HIGH); 
  analogWrite(RIGHT_SPEED, c_motor_speed);
  analogWrite(LEFT_SPEED, c_motor_speed);
  if(duration > 0){
    delay(duration);
  }
}

void Stop() {
  digitalWrite(RIGHT_FORWARD, LOW);  
  digitalWrite(RIGHT_REVERSE ,LOW); 
  digitalWrite(LEFT_FORWARD, LOW);  
  digitalWrite(LEFT_REVERSE , LOW); 
  analogWrite(RIGHT_SPEED, c_motor_speed);
  analogWrite(LEFT_SPEED, c_motor_speed);
}

void LEDColor(String color) {
  if(color == "red") {
    digitalWrite(LED_R, HIGH); 
    digitalWrite(LED_G, LOW); 
    digitalWrite(LED_B, LOW); 
  }
  else if(color == "green"){
    digitalWrite(LED_R, LOW); 
    digitalWrite(LED_G, HIGH); 
    digitalWrite(LED_B, LOW); 
  }
  else if (color == "blue") {
    digitalWrite(LED_R, LOW); 
    digitalWrite(LED_G, LOW); 
    digitalWrite(LED_B, HIGH);     
  }
  else if(color == "off") {
    digitalWrite(LED_R, LOW); 
    digitalWrite(LED_G, LOW); 
    digitalWrite(LED_B, LOW);  
  }
}

void CenterHead() {
    servoPosition =90;
    myservo.write(servoPosition);
}

String msg;
void setup() {
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);

  pinMode(EchoPin, INPUT);
  pinMode(TrigPin, OUTPUT);

  myservo.attach(ServoPin);
  myservo.write(servoPosition);
  Serial.begin(9600);
  int startDelay = 0;
  // delay ten sec at startup
    while(10 > startDelay){
    LEDColor("red");
    delay(500);
    LEDColor("off");
    delay(500);
    startDelay++;
  }
}

void loop() {

   if (Serial.available() > 0){ // Check if there is data coming
    msg = Serial.readString(); // Read the message as String
    if(msg == "stop") {
      manualControl = true;
      Stop();
      CenterHead();
      LEDColor("red");
    }
    else if(msg == "go") {
      LEDColor("green");
      manualControl = false;
      DriveForward(1);
    }
    msg = "";
   }
  if(manualControl) {
    return;
  }
  double forwardDistance = 500;
  if(deepScan) {
    LEDColor("blue");
    delay(10);
  }
  if(!deepScan){
    forwardDistance = GetDistance(EchoPin, TrigPin);
  }
  if(forwardDistance > c_maxDistance) {
    forwardDistance = TurnHeadAndGetDistance();
  }

  if(forwardDistance < c_stopDistance) {
    Serial.println("Action: STOP");
    LEDColor("red");
    if(!deepScan){
      Reverse(500);
      // start scanning in opposite direction as we were turning when we encountered this obstacle
      turningRight = !turningRight;
    }
    Stop();
    // we will remain stopped until we exit the deepScan state
    deepScan = true;
    delay(500);
  }
  else{
    // if deep scan is true we just came out of red light (stopped) state
    if(deepScan){
      // we want to turn in the direction we are looking since we found a path
      deepScan = false;
      LEDColor("green");
      delay(500);
      LEDColor("off");
      delay(500);
      LEDColor("green");
      if(servoPosition < 90) {
        int duration = 90 - servoPosition;
        // we want to turn in the direction of the head
        SpinRight(duration*c_vehicleTurnRate);
      }
      else {
        int duration = servoPosition - 90;
        SpinLeft(duration*c_vehicleTurnRate);
      }
      CenterHead();
      DriveForward(1);
    }
    // blue light case
    else if(forwardDistance < c_maxDistance) {
      // in this case we want to turn away from the direction of the servo since it detected a distant obstacle
      LEDColor("blue");
      if(servoPosition < 90) {
        int duration = -1*(c_scanMin - servoPosition);
        Serial.println("Action: turn left for " + String(duration));
        SpinLeft(duration*c_vehicleTurnRate);
        CenterHead();
        // start turning head in the direction of obstacle again
        turningRight = true;
      }
      else {
        Serial.println("Action: drive right");
        int duration = -1*(servoPosition - c_scanMax );
        Serial.println("Action: turn right for " + String(duration));
        SpinRight(duration*c_vehicleTurnRate);
        CenterHead();
        // start turning head in the direction of obstacle again
        turningRight = false;
      }
      DriveForward(1);
    }
    else {
      LEDColor("green");
      DriveForward(1);
    }
  } 
}
