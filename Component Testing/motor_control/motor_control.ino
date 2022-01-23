#define RED 11
#define GREEN 10
#define BLUE 9

#define LEFT_REVERSE  7 
#define LEFT_FORWARD 8
#define LEFT_SPEED  6

#define RIGHT_FORWARD  2
#define RIGHT_REVERSE  4
#define RIGHT_SPEED  5


int motor_speed = 70;

void DriveForward(int duration) {
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_REVERSE , LOW);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_REVERSE , LOW);
  analogWrite(RIGHT_SPEED, motor_speed);
  analogWrite(LEFT_SPEED, motor_speed);
  delay(duration);
}

void Reverse(int duration) {
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE , HIGH);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_REVERSE , HIGH);
  analogWrite(RIGHT_SPEED, motor_speed);
  analogWrite(LEFT_SPEED, motor_speed);
  delay(duration);
}

void SpinRight(int duration) {
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE , HIGH);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_REVERSE , LOW);
  analogWrite(RIGHT_SPEED, motor_speed);
  analogWrite(LEFT_SPEED, motor_speed);
  delay(duration);
}

void SpinLeft(int duration) {
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_REVERSE , LOW);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_REVERSE , HIGH);
  analogWrite(RIGHT_SPEED, motor_speed);
  analogWrite(LEFT_SPEED, motor_speed);
  delay(duration);
}

void Stop() {
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE , LOW);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_REVERSE , LOW);
  analogWrite(RIGHT_SPEED, motor_speed);
  analogWrite(LEFT_SPEED, motor_speed);
}

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
  Serial.begin(9600); 
}


void loop() {
  delay(5000);
  Serial.println("Driving Forward for 5 seconds");
  DriveForward(5000);
  Stop();
  delay(1000);
  Serial.println("Reverse for 5 seconds");
  Reverse(5000);
  Stop();
  delay(1000);
  Serial.println("Driving Left for 5 seconds");
  SpinLeft(5000);
  Stop();
  delay(1000);
  Serial.println("Driving Right for 5 seconds");
  SpinRight(5000);
  Stop();
  delay(1000);

}
