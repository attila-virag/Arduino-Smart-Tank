#define RED 11
#define GREEN 10
#define BLUE 9

String msg;
void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  Serial.begin(9600); // Communication rate of the Bluetooth Module
}

void loop() {
 // To read message received from other Bluetooth Device
 //Serial.println("");
 delay(500);
  if (Serial.available() > 0){ // Check if there is data coming
    msg = Serial.readString(); // Read the message as String
    Serial.println("Serial Command: " + msg);
    if(msg == "red on") {
      digitalWrite(RED, HIGH); // Turn on LED
      msg = "";
    }
    else if(msg == "red off") {
      digitalWrite(RED, LOW); 
      msg = "";
    }

    else if(msg == "green on") {
      digitalWrite(GREEN, HIGH); // Turn on LED
      msg = "";
    }
    else if(msg == "green off") {
      digitalWrite(GREEN, LOW); 
      msg = "";
    }

    else if(msg == "blue on") {
      digitalWrite(BLUE, HIGH); // Turn on LED
      msg = "";
    }
    else if(msg == "blue off") {
      digitalWrite(BLUE, LOW); 
      msg = "";
    }
    else {
      Serial.println("Unknown Command");
    }
  }

  
}
