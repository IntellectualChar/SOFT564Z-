// ---------------------------------------------------------
// TEST CODE FOR INTERGRATION OF SERVO AND ULTRASONIC SENSOR
// Charlotte Perry 2020
// ---------------------------------------------------------

#define echoPin 2 // attach pin D2
#define trigPin 4 //attach pin D3
#include <Servo.h>

Servo servo1;  // create servo object
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance
int pos = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); 
  Serial.println("Ultrasonic Sensor and servo Test"); 
  servo1.attach(5);  // attaches the servo on pin 5
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; 
  // Displays the distance on the Monitor
  if(distance < 25)
  {
    
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
       servo1.write(pos);                 // go to position in variable 'pos'
       delay(15);                         // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) {   // goes from 180 degrees to 0 degrees
    servo1.write(pos);                    // go to position in variable 'pos'
    delay(15);                            // waits 15ms for the servo to reach the position
  }
}
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(300);
}
