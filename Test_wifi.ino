// ---------------------------------
// Test ESP32 connect to WiFi
// Charlotte Perry 2020
// ---------------------------------

#include <WiFi.h>        

const char* ssid = "24 RADNOR TOP";
const char* password = "cdn3cjqfCmX8";

void setup() {
  Serial.begin(115200);                  // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);            // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Print IP address of the ESP32 
}

void loop() { 
  
}
