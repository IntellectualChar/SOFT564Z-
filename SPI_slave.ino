//--------------------------------------------------------
// SPI SLAVE CODE FOR ARDUINO MEGA
// Charlotte Perry 2021
//--------------------------------------------------------

#include "SPI.h"
#include <Servo.h>
#include <IRremote.h>
#define echoPin 2 // attach pin D2
#define trigPin 4 //attach pin D4

// Creating objects and variables for SPI
char buff [50];
volatile byte indx;
volatile boolean process;
char info[] = "I'm too close to something, help!\n";

// Creating objects and variables for sensors and actuators
Servo servo1;  // create servo object
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance
int pos = 0;

// Creating objects and variables for IR receiver and remote
const int RECV_PIN = 7;       // Set pin 7 as signal from receiver
IRrecv irrecv(RECV_PIN);      // Set receive pin data as irrecv
decode_results results;       
unsigned long key_value = 0;  // Set key value as 0 to start

void setup (void) {
   Serial.begin (9600);       // Start serial monitor at baudrate 9600
   pinMode(MISO, OUTPUT); 
   SPCR |= _BV(SPE);          // turn on SPI in slave mode
   indx = 0;                  // start 0buffer empty
   process = false;
   SPI.attachInterrupt();     // turn on interrupt
   // Set up for sensors and actuator
   pinMode(trigPin, OUTPUT);  // Sets the trigPin as an OUTPUT
   pinMode(echoPin, INPUT);   // Sets the echoPin as an INPUT
   Serial.println("Ultrasonic Sensor and servo Test"); 
   servo1.attach(10);         // attaches the servo on pin 10
   irrecv.enableIRIn();        // Set irrecv as input
   irrecv.blink13(true);       // Blink onboard LED when signal from remote received
}

ISR (SPI_STC_vect)  
{ 
   byte c = SPDR; // read byte from SPI Data Register
   if (indx < sizeof buff) { 
      if (c == '\0') 
      process = true;
      if(distance < 25) {
        SPDR = info[indx]; //save part of the string in the SPI data register
        buff [indx++] = c; // save data in the next index in the array buff
      }
   }
}

void loop (void) {
   if (process) {
      process = false; //reset the process

      // run sensor and actuator code
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
        Serial.println(distance); // Displays the distance on the Monitor
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
      if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;
          
        // Switch cases to print the value of the key pressed
        switch(results.value){
          case 0xFFA25D:
          Serial.println("1");
          break;
          case 0xFF629D:
          Serial.println("2");
          break;
          case 0xFFE21D:
          Serial.println("3");
          break;
          case 0xFF22DD:
          Serial.println("4");
          break;
          case 0xFF02FD:
          Serial.println("5");
          break ;  
          case 0xFFC23D:
          Serial.println("6");
          break ;               
          case 0xFFE01F:
          Serial.println("7");
          break ;  
          case 0xFFA857:
          Serial.println("8");
          break ;  
          case 0xFF906F:
          Serial.println("9");
          break ;  
          case 0xFF9867:
          Serial.println("0");
          break ;  
          case 0xFF6897:
          Serial.println("*");
          break ;
          case 0xFFB04F:
          Serial.println("#");
          break ;
          case 0xFF18E7:
          Serial.println("^");
          break ;
          case 0xFF5AA5:
          Serial.println(">");
          break ;
          case 0xFF10EF:
          Serial.println("<");
          break ;
          case 0xFF4AB5:
          Serial.println("V");
          break ;
          case 0xFF38C7:
          Serial.println("ok");
          break ;     
        }
        key_value = results.value;
        irrecv.resume(); 
   }  
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
        delay(300);
      
      //Serial.println (info); //print the recieved message on serial monitor
      //Serial.print("helllo");
      indx= 0; //reset button to zero
   }

 //Serial.print(info);
}
