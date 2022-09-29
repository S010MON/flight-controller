#include <SoftwareSerial.h>

const byte Rxd = 4;
const byte Txd = 5;

SoftwareSerial HC12(Txd, Rxd);

void setup() 
{
  Serial.begin(9600);
  HC12.begin(9600);
}

void loop() 
{
  while(HC12.available())
  {
    Serial.print(HC12.read());
  }
  while(Serial.available())
  {
    HC12.write(Serial.read());
  }
}
