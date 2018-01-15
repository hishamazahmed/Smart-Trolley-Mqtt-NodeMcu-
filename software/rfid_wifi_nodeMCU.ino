#include <ESP8266WiFi.h>
#include <RFID.h>
#include <SPI.h>
#define RST_PIN 5
#define SS_PIN 4


const char *ssid =  "FreeWifi";        
const char *pass =  "iotthink";
const char* serverTS = "api.thingspeak.com";
String apiKey = "YHICNFP4BXIY4ZV3";          //Insert your Channel API Key here

RFID rfid(SS_PIN,RST_PIN);  
String uidString;

void setup() 
{
  SPI.begin(); 
  rfid.init();  
  Serial.begin(115200);         //Recommended speed is 115200
  connectWifi();
  }

void loop() 
{

 if(rfid.isCard())
   {    
        if(rfid.readCardSerial()){

    uidString = String(rfid.serNum[0])+String(rfid.serNum[1])+String(rfid.serNum[2])+String(rfid.serNum[3])+String(rfid.serNum[4]);
    Serial.println(uidString);//7011723314773
    delay(400);

    int rfiduid=uidString.toInt();

     sendRfid(rfiduid);
 delay(1000);
    
  }
    rfid.halt();
  }
  

 
 
}
void connectWifi()
{ 
  Serial.print("Connecting to "+*ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
  Serial.println("");  
}//end connect

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

 void sendRfid(int sensorVoltage)
{  
  WiFiClient tclient;//not to be confused with "client" in PubSub{}, and wclient for mqtt
   if (tclient.connect(serverTS, 80)) { // use ip 184.106.153.149 or api.thingspeak.com
   //Serial.println("WiFi Client connected ");
   
   String postStr = apiKey;
   postStr += "&field3=";
   postStr += String(sensorVoltage);
   postStr += "\r\n\r\n";
   
   tclient.print("POST /update HTTP/1.1\n");
   tclient.print("Host: api.thingspeak.com\n");
   tclient.print("Connection: close\n");
   tclient.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
   tclient.print("Content-Type: application/x-www-form-urlencoded\n");
   tclient.print("Content-Length: ");
   tclient.print(postStr.length());
   tclient.print("\n\n");
   tclient.print(postStr);
   delay(1000);
   
   }//end if

 tclient.stop();
}//end send to ts
