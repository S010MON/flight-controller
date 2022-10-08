/* 1byte HC12 Receiver example.
/* Tutorial link: http://electronoobs.com/eng_arduino_tut96.php
 * Code: http://electronoobs.com/eng_arduino_tut96_code1.php
 * Scheamtic: http://electronoobs.com/eng_arduino_tut96_sch1.php
 * Youtube Channel: http://www.youtube/c/electronoobs   
 * 
  Module // Arduino UNO/NANO    
    GND    ->   GND
    Vcc    ->   3.3V
    Tx     ->   D10
    Rx     ->   D11      
 */
#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
int LED = 3;

void setup() 
{
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pinMode(LED,OUTPUT);
}

void loop() 
{
  while (HC12.available())  // If HC-12 has data
  {       
    char val = HC12.read();
    Serial.println(HC12.read());      // Send the data to Serial monitor
    //analogWrite(LED,val);
  }  
}
