int s1=13;
void setup() 
{
Serial.begin(9600); 
pinMode(s1,INPUT);/* initialise serial communication */
}

void loop()
{
  if(digitalRead(s1)==HIGH)
    {
      Serial.println("white"); /* print Electronic Wings at new line per second */
    }
  else 
   {
    Serial.println("black");
   }
}
