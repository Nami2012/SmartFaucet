#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

#include <ESP8266WiFi.h>
#include <SPI.h>
#include "HX711.h" 
#define DOUT  4
#define CLK  5
int offset =20;
int weight;
int IR=4;
int V=A0;
int SV = 15;
int B=13;
HX711 scale(DOUT, CLK);
float calibration_factor = -106600;

 
const char* ssid = "SSID";
const char* password = "password";
 
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
   
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   
scale.set_scale(calibration_factor); 
pinMode(IR,INPUT);
pinMode(V.INPUT);
pinMode(SV,OUTPUT);
pinMode(B,OUTPUT);

  }
 
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
}
 
void loop() {
  // Check if a client has connected
   weight = scale.get_units()*10;  //obtain weight from load cell
   //read voltage
  int volt = analogRead(V);// read the input
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
   voltage /=100;// divide by 100 to get the decimal Values
 if (voltage>6.00)
    {digitalWrite(B,LOW);
      if(digitalRead(IR)==HIGH)
             {  WiFiClient client = server.available();
                if (!client) {
                 while(digitalRead(IR)==HIGH)
                 digitalWrite(SV,HIGH);
                  
              }
              else{
                 // Read the first line of the request
                 String request = client.readStringUntil('\r');
                 Serial.println(request);
                 client.flush();
 
                 // Match the request
  
  
                 if (request.indexOf("/weight=300g") != -1)  {
    
                      while((digitalRead(IR)==HIGH)&&(wv>300))
                      digitalWrite(SV,HIGH);
                  }
                 if (request.indexOf("/weight=500g") != -1)  {
                      while((digitalRead(IR)==HIGH)&&(wv>500))
                      digitalWrite(SV,HIGH);
   
                  }
              }
     else
       {
        digitalWrite(SV,LOW);
        }
     }
    
    else
    {
      while( voltage <6.00)
         digitalWrite(B,HIGH);
    }
 }
 

 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Enter Weight");

  client.println("<br><br>");
  client.println("<a href=\"/weight=300\"\"><button>300</button></a>");
  client.println("<a href=\"/weight=500\"\"><button>500 </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
} 

