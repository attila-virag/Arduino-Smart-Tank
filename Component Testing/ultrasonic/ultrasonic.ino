int LED_R = 11;     
int LED_G = 10;     
int LED_B = 9;      

int EchoPin = 12;             
int TrigPin = 13;             

const double SPEED_OF_SOUND = 0.0343; // cm per microsecond

long GetDistance() {

  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  // send a 10 microsec sound burst
  digitalWrite(TrigPin, HIGH);
  // wait until sound burst complete
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  // read echo pin
  long duration = pulseIn(EchoPin, HIGH);
  return duration * SPEED_OF_SOUND / 2; 
  
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
}

void setup() {
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);

  pinMode(EchoPin, INPUT);
  pinMode(TrigPin, OUTPUT);
}

void loop() {

 delay(100);

  long distance = GetDistance();

  if(distance < 20) {
    LEDColor("red");
  }
  else if(distance < 50) {
    LEDColor("blue");
  }
  else{
    LEDColor("green");
  }
  
}
