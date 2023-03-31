#include <SoftwareSerial.h> //allow for serial communication for HC-12
#include <Wire.h>
#include <SFE_BMP180.h> //Sparkfun BMP library

//Connect BMP180 to Arduino (Uno or nano)
//VIN - Connect to Arduino 3.3 or 5 V
//GND - Connect to Arduino GND
//SCL - Connect to Arduino A5
//SDA - Connect to Arduino A4

//Connect HC-12 to Arduino
//VCC - Connect to Arduino 3.3V
//GND - Connect to Arduino GND
//TX - Connect to Arduino pin 2 (RX)
//RX - Connect to Arduino pin 3 (TX)

SFE_BMP180 bmp180; //create object

//SoftwareSerial hc12(2,3); //RX, TX
//test

//decide if measuring altitude relative to sea level or relative to ground, (sea level easier imo)
float Po = 1013.0 //altitude relative to sea level

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //pass value 9600(9600 binary bits/second, aka baud rate) to speed parameter - starts serial communication so arduino can send commands thru USB connection
  
  hc12.begin(9600);

  bool success = bmp180.begin(); //.begin retrieve bidirectional iterator aka pointer to first element of data structure

  if (success) {
    Serial.println("BMP180 init success") //initialize sensor, upon success, it returns non zero value
    
    else{
      Serial.println("fail. wiring issue")
      while (1) {}
    }
  }
}


void sendHeader(){ //header of hc12 data
  hc12.print("TEMP | PRESSURE | ALTITUDE");
}

void sendData(double T, double P, double alt){ //fxn to send data from bmp to hc12
  sendHeader();  
  hc12.print(T + "  " + P + "  " + alt);
  hc12.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  char status;
  double T, P, alt;
  bool success = false;

  status = bmp180.startTemperature(); //according to flowchart on order bmp reads data, on success, returns non zero value

if (status != 0) {
    delay(1000);
    status = bmp180.getTemperature(T); //wait 4.5 ms, function recieve value, store in T

    if (status != 0) {
      status = bmp180.startPressure(3); //sends command to start pressure measurement, 3 is provided as an oversampling value, returns number of ms Arduino needs to wait before reading pressure value from sensor

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T); //read pressure value, store in P, *also pass in T since pressure calculation is dependent on temp
          
        if (status != 0) {
            alt = bmp180.altitude(P, Po); //calculating altitude w formula in library from the pressure

            Serial.print("Altitude: ");
            Serial.print(alt);
            Serial.println(" Meters");

            Serial.print("Pressure: ");
            Serial.print(P);
            Serial.println(" hPa");

            Serial.print("Temperature: ");
            Serial.print(T);
            Serial.println(" C");

            sendData(T, P, alt); //call function to send data to hc12
        }
      }
    }
  } 
}
