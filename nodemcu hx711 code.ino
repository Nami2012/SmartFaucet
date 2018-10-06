/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 *
 * This example shows how to use ESP8266 Shield (with AT commands)
 * to connect your project to Blynk.
 *
 * Note: Ensure a stable serial connection to ESP8266!
 *       Firmware version 1.0.0 (AT v0.22) is needed.
 *       You can change ESP baud rate. Connect to AT console and call:
 *           AT+UART_DEF=9600,8,1,0,0
 *       In general, Soft Serial may be unstable.
 *       It is highly recommended to switch to Hard Serial.
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 * Feel free to apply it to any other example. It's simple!
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include "HX711.h"

// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0

HX711 scale(D1, D0);    // parameter "gain" is ommited; the default value 128 is used by the library

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2b4160f0556c452797b82e0555fd48ca";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "fukat";
char pass[] = "akshay1234";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

void setup()
{
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided 
            // by the SCALE parameter (not set yet)  

  scale.set_scale(6017.4159836065);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
  // Set console baud rate
  Serial.begin(9600);
  delay(10);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);
  Blynk.virtualWrite(V5, scale.get_units(), 1);
  scale.power_down();              // put the ADC in sleep mode
  delay(500);
  scale.power_up();

  Blynk.run();
}

