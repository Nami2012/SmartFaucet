
 /*
 * This is the Arduino code for  Voltage Sensor
 * you will measure voltage using this module which eliminate use extra resistors
 in the video also you will learn how to measure any voltages.

 * Watch the video instruction for Arduino Voltage sensor https://youtu.be/FaoKzi7tgME
 *  * 

 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * 
 */
/*
 * Written by Ahmad Shamshiri for Robojax
 * on Feb 07, 2018 at 20:05, Ajax, Ontario, Canada
 */
int offset =20;// set the correction offset value
void setup() {
  // Robojax.com voltage sensor
  Serial.begin(9600);
}

void loop() {
  // Robojax.com voltage sensor
  int volt = analogRead(A0);// read the input
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  
  voltage /=100;// divide by 100 to get the decimal values
  Serial.print("Voltage: ");
  Serial.print(voltage);//print the voltge
  Serial.println("V");

delay(500);
  
  
}
