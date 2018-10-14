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
void setup() {
scale.set_scale(calibration_factor); 
pinMode(IR,INPUT);
pinMode(V.INPUT);
pinMode(SV,OUTPUT);
pinMode(B,OUTPUT);
}

void loop() {
 weight = scale.get_units()*10;  //obtain weight from load cell
 //read voltage
  int volt = analogRead(V);// read the input
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
   voltage /=100;// divide by 100 to get the decimal Values
 
 if (voltage>6.00)
    {
      if(digitalRead(IR)==HIGH)
         {int wv=client.data();
          if(wv == NULL) 
              {
                while(digitalRead(IR)==HIGH)
                 digitalWrite(SV,HIGH);
                  
              }
          else{
            while((digitalRead(IR)==HIGH)&&(wv>weight))
            digitalWrite(SV,HIGH);
            }
       else
       {
        digitalWrite(SV,HIGH);}
    
    else
    {
      while( voltage <6.00)
         digitalWrite(B,HIGH);
    }
 }
         
       
            
          
    

   
