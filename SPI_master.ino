// ---------------------------------
// Master code for the ESP32
// Charlotte Perry 2021
// ---------------------------------

#include "SPI.h"
#include <WiFi.h>

char buff[]="Hello Slave\n";            //test message to send to slave
char buff2[]="Hi i want info\n";        // Request for information from the slave
char returnbyte;                        // Variable to store information from the slave
// network credentials
const char* ssid = "24 RADNOR TOP";
const char* password = "cdn3cjqfCmX8";


WiFiServer server(80);                  // Set web server port number to 80
String header;                          // To store the HTTP request
unsigned long currentTime = millis();   // Current time
unsigned long previousTime = 0;         // The previous time
const long timeoutTime = 2000;          // Timeout time in milliseconds


void setup() {
 Serial.begin(115200);                      // Start serial monitor at 115200
 SPI.begin(18, 19, 23, 05);                 //setting SPI pins
 SPI.setClockDivider(SPI_CLOCK_DIV8);
 pinMode(05, OUTPUT);                       //setting pin 5 as output
 digitalWrite(05, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {   // Wait for connection to Wi-Fi
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
   WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {                             // If a new client connects continue
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read the byte
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
                        
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
        
//            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
//            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//            client.println(".button2 {background-color: #555555;}</style></head>");
            
            
            client.println("<body><h1>ESP32 Web Server</h1>"); // Web Page Heading

            client.println("<body><h2>HELLO IT WORKED</h2>");  // Test text

             digitalWrite(05, LOW); 
             for(int i=0; i<sizeof buff2; i++)
             {
               returnbyte = SPI.transfer(buff2[i]);   // Get string from SPI data register sent by slave
               Serial.print(returnbyte);              // Print message from slave
               client.println(returnbyte);            // Print received message on the server page
             }
             digitalWrite(05, HIGH);
             
             delay(1000);  
            
            // The HTTP response ends with another blank line
            client.println();
            break;
          } else {                                    // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {                      // if you got anything else but a carriage return character,
          currentLine += c;                          // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    //header = "";
    //client.stop();                                   // Close the connection
    //Serial.println("Client disconnected.");
    //Serial.println("");
  }
}
