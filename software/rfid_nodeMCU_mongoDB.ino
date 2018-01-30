//NODEMCU-RFID522 pin configuration:

//3.3V-3.3V
//RST-D1
//GND-GND
//MISO-D6
//MOSI- D7
//SCK- D5
//SDA- D2




#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include <RFID.h>
#include <SPI.h>
#define RST_PIN 5
#define SS_PIN 4

RFID rfid(SS_PIN,RST_PIN);  
String uidString;

void setup() {
  SPI.begin(); 
  rfid.init(); 
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("DataSoft_WiFi", "support123");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
   }
}
 
void loop() {

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
  JsonObject& JSONencoder = JSONbuffer.createObject(); 

     if(rfid.isCard())
   {    
        if(rfid.readCardSerial()){

    uidString = String(rfid.serNum[0])+String(rfid.serNum[1])+String(rfid.serNum[2])+String(rfid.serNum[3])+String(rfid.serNum[4]);
    Serial.println(uidString);//7011723314773
    delay(400);
  
    }
    rfid.halt();

    JSONencoder["sensorType"] = "rfid";
    JSONencoder["value"] = uidString;
    JSONencoder["timestamp"] = "09-01-2018";
 
   
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);

 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://192.168.4.37:5000/sensor");      //Specify request destination
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
