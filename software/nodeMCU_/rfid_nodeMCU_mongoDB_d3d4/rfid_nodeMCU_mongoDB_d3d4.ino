//NODEMCU-RFID522 pin configuration:

//3.3V-3.3V
//RST-D1
//GND-GND
//MISO-D6
//MOSI- D7
//SCK- D5
//SDA(SS)- D2

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "RFID.h"
#include <SPI.h>
#define SS_PIN      D3      // Same pin used as hardware SPI (SS)
#define RST_PIN     D4
#define MOSI_PIN    D7      // hardware SPI: A5
#define MISO_PIN    D6      //     "     " : A4
#define SCK_PIN     D5      //     "     " : A3
#if defined(_USE_SOFT_SPI_)
    RFID RC522(SS_PIN, RST_PIN, MOSI_PIN, MISO_PIN, SCK_PIN);    // Software SPI
    #else
   RFID RC522(SS_PIN, RST_PIN);                                 // Hardware SPI
#endif

//RFID rfid(SS_PIN,RST_PIN);  
String uidString;

void setup() {
  SPI.begin(); 
  RC522.init(); 
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("FreeWifi", "iotthink");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
   }
   Serial.println("Connected");
}
 
void loop() {

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  //Serial.println("Connected");
  StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
  JsonObject& JSONencoder = JSONbuffer.createObject(); 

     if(RC522.isCard())
   {    
        if(RC522.readCardSerial()){

    uidString = String(RC522.serNum[0])+String(RC522.serNum[1])+String(RC522.serNum[2])+String(RC522.serNum[3])+String(RC522.serNum[4]);
    Serial.println(uidString);//7011723314773
    delay(400);
  
    }
    RC522.halt();

    JSONencoder["sensorType"] = "rfid";
    JSONencoder["value"] = uidString;
    JSONencoder["timestamp"] = "09-01-2018";
 
   
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);

 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://192.168.4.66:5000/sensor");      //Specify request destination
   http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
   int httpCode = http.POST(JSONmessageBuffer);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
   http.end();  //Close connection

delay(1000);
  }
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
 
}
