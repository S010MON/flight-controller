#include <SoftwareSerial.h>
#include <Servo.h>

#define DEBUG 0
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

int x = 90;
int y = 90;
int z = 90;
int p = 0;

int x_new;
int y_new;
int z_new;
int p_new;

int pntr = 0;
int packet[10]; 

int sensitivity = 2;

void setup() 
{
  Serial.begin(9600);
  HC12.begin(9600);
}

void loop() 
{
   if(HC12.available())
   {
      int currentChar = HC12.read();
      if(currentChar != '\n')
      {
        packet[pntr++] = currentChar;
        currentChar = HC12.read();      
      }
      else
      {       
        // DEBUGGING
        for(int i = 0; i < 4; i++)
        {
          debug(packet[i]);
          debug(" ");
        }

        if(pntr != 4)
        {
          debugln(" Packet failed");
          pntr = 0;
        }
        else
        {
          x_new = packet[0];
          y_new = packet[1];
          z_new = packet[2];
          p_new = packet[3];
  
          if(abs(x_new - x) > sensitivity)
          {
            x = x_new;
            Serial.write('x');
            Serial.write(x);
          }
  
          if(abs(y_new - y) > sensitivity)
          {
            y = y_new;
            Serial.write('y');
            Serial.write(y);
          }
  
          if(abs(z_new - z) > sensitivity)
          {
            z = z_new;
            Serial.write('z');
            Serial.write(z);
          }
          Serial.write('\n');
        }
        
        pntr = 0;
      }
   }
}
