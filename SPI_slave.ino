#include "SPI.h"
char buff [50];
volatile byte indx;
volatile boolean process;

char info[] = "hello master\n";

void setup (void) {
   Serial.begin (9600);
   pinMode(MISO, OUTPUT); 
   SPCR |= _BV(SPE); // turn on SPI in slave mode
   indx = 0; // buffer empty
   process = false;
   SPI.attachInterrupt(); // turn on interrupt
}

ISR (SPI_STC_vect)  
{ 
   byte c = SPDR; // read byte from SPI Data Register
   if (indx < sizeof buff) { 
      if (c == '\0') 
      process = true;
      SPDR = info[indx];
      buff [indx++] = c; // save data in the next index in the array buff
   }
}

void loop (void) {
   if (process) {
      process = false; //reset the process
      
      //Serial.println (info); //print the recieved message on serial monitor
      Serial.print("helllo");
      indx= 0; //reset button to zero
   }

 //Serial.print(info);
}
