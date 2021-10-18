#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  Serial.begin(115200);                                 //Serial connection
  WiFi.begin("CMT_M-1", "EMuema@123");                  //WiFi connection
  while (WiFi.status() != WL_CONNECTED) {               //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {                  //Check WiFi connection status
    HTTPClient http;                                    //Declare object of class HTTPClient
    WiFiClient client;
    http.begin(client, "http://snippet.io.ke/tal/");    //Specify request destination
    http.addHeader("Content-Type", "text/plain");       //Specify content-type header
    int value = random(1000);
    int httpCode = http.POST(String(value));            //Send the request
    String payload = http.getString();                  //Get the response payload
    Serial.write(httpCode);                             //Print HTTP return code
    Serial.println(payload);                            //Print request response payload
    http.end();                                         //Close connection
  }
  else {
    Serial.println("Error in WiFi connection");
  }
  delay(5000);                                          //Send a request every x(1000) seconds
}
