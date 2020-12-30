/*
Motor Test
Charlotte Perry 30/11/2020
*/

#include <Servo.h>

Servo servo1;  //Creating a Servo object to control 

int pos = 0;    //Creating Position variable and setting to 0

void setup() {
  servo1.attach(9);  //Sets up the Servo on pin 9 as Servo1
}

//Loop for continuous movement of the servo and therfore wheels to check the mechanics

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { //Movement from 0 to 180 degrees
    servo1.write(pos);              //Sending the value of the positin to the servo
    delay(20);                       //Waits 20ms
  }
  //Move the servo back in the opposite direction
  for (pos = 180; pos >= 0; pos -= 1) { //Movement from 180 to 0 degrees
    servo1.write(pos);              
    delay(20);                       //Waits 20ms
  }
}
