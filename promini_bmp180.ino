//
// Arduino Pro Mini - BMP180 reader
//
// BMP180 pins: 
//    SDA - A4, SCL - A5, VCC via LED to VCC, GND - GND
//
// library: 
//    https://github.com/adafruit/Adafruit-BMP085-Library
//
// Output protocol (9600 baud):
//  <short blink>
// t=99.9
// p=1013
//  <long blink>
//  <pause>
//
// Sensor failure:
//  <short blink>
// !BMP
//  <pause>

const char* VER = "promini_bmp180-1.0.0";

const int BLINK_SHORT =  250;
const int BLINK_LONG  = 1000;
const int PAUSE       = 5000;   // 5 seconds
const int LED_PIN     = 13;

#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {                
  pinMode(LED_PIN, OUTPUT);     
  Serial.begin(9600);
  Serial.print("= ");
  Serial.println(VER);
}

int read_data()
{
  if(!bmp.begin()) {
    return false;
  }

  Serial.print("t=");
  Serial.println(bmp.readTemperature());
  
  Serial.print("p=");
  Serial.println(bmp.readPressure()*0.01);
  
  return true;
}

void loop() 
{
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_SHORT);
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  
  if(read_data()) {
    delay(BLINK_SHORT);
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_LONG);
    digitalWrite(LED_PIN, LOW);
  }
  else {
    Serial.println("!BMP");
  }
  
  delay(PAUSE);
}

//.
