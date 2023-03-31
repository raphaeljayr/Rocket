// (Sending Data)
#include <SoftwareSerial.h>
SoftwareSerial HC12(11,10); // HC-12 TX Pin, HC-12 RX Pin

void setup()
{
  Serial.begin(9600); //can be changed later
  HC12.begin(9600);
}

void loop()
{
  String GPS_DATA, BARO_DATA;//placeholder for when we have official working code for GPS and Barometer all compiled together.
  String allData = String(GPS_DATA + " " + BARO_DATA);
  Seria.print(allstring);
  HC12.print(allstring);
  delay(3000);
}
