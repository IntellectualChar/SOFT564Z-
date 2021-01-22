// ----------------------------------------
// IR Receiver and IR Remote test
// Charlotte Perry 2021
// ----------------------------------------

#include <IRremote.h>

const int RECV_PIN = 7;       // Set pin 7 as signal from receiver
IRrecv irrecv(RECV_PIN);      // Set receive pin data as irrecv
decode_results results;       
unsigned long key_value = 0;  // Set key value as 0 to start

void setup(){
  Serial.begin(9600);         // Start serial at 9600 baudrate
  irrecv.enableIRIn();        // Set irrecv as input
  irrecv.blink13(true);       // Blink onboard LED when signal from remote received
}

void loop(){
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
}
