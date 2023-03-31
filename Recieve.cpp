#include <SoftwareSerial.h>
SoftwareSerial HC12(10,11);

void setup() {
  Serial.begin(9600);
  HC12.begin(9600); 
}

void loop() 
{   
  if (HC12.available())
  {
    Serial.println(HC12.readStringUntil('\n'));
  }  
}
