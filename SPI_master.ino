#include "SPI.h"
char buff[]="Hello Slave\n"; //test message to send to slave

void setup() {
 SPI.begin(18, 19, 23, 05);  //setting SPI pins
 SPI.setClockDivider(SPI_CLOCK_DIV8);
 pinMode(05, OUTPUT); //setting pin 5 as output
 digitalWrite(05, LOW);
}

void loop() {
 digitalWrite(05, LOW); 
 for(int i=0; i<sizeof buff; i++)
 {
  SPI.transfer(buff[i]); //send the message to the slave
 }
 digitalWrite(05, HIGH);
 delay(1000);  
}
