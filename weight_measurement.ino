#include <SPI.h>

#include "HX711.h"  //You must have this library in your arduino library folder
 
#define DOUT  12
#define CLK  13
 
HX711 scale(DOUT, CLK);
 
//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -106600; //-106600 worked for my 40Kg max scale setup 
 
//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  Serial.begin(9600);  
  Serial.println("Press T to tare");
  scale.set_scale(-106600);  //Calibration Factor obtained from first sketch
  scale.tare();             //Reset the scale to 0  
}
 
//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {
  Serial.print("Weight: ");
  Serial.print(scale.get_units()*10, 3);  //Up to 3 decimal points
  Serial.println(" gms"); //Change this to kg and re-adjust the calibration factor if you follow lbs
 delay(1000);
}
