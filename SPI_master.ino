#include "SPI.h"
char buff[]="Hello Slave\n"; //test message to send to slave
char buff2[]="Hi i want info\n";
char returnbyte;

void setup() {
 Serial.begin(115200);
 SPI.begin(18, 19, 23, 05);  //setting SPI pins
 SPI.setClockDivider(SPI_CLOCK_DIV8);
 pinMode(05, OUTPUT); //setting pin 5 as output
 digitalWrite(05, LOW);
}

void loop() {
 digitalWrite(05, LOW); 
 for(int i=0; i<sizeof buff2; i++)
 {
   returnbyte = SPI.transfer(buff2[i]);   //SPI.transfer(buff[i]); //send the message to the slave
   Serial.print(returnbyte);
   //Serial.println('\n');
 }

 digitalWrite(05, HIGH);
 
 delay(1000);  
}
