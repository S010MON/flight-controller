#include <SoftwareSerial.h>
#include <Servo.h>

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

#define AILERON_L_PIN 12
#define AILERON_R_PIN 9
#define ELEVATOR_L_PIN 6
#define ELEVATOR_R_PIN 5
#define RUDDER_PIN 3

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

Servo ailr_l;
Servo ailr_r;
Servo elvr_l;
Servo elvr_r;
Servo rudder;

int x = 90;
int y = 90;
int z = 90;
int p = 0;

int pntr = 0;
int packet[4]; 

void setup() 
{
  Serial.begin(9600);
  HC12.begin(9600);

  ailr_l.attach(AILERON_L_PIN);
  ailr_r.attach(AILERON_R_PIN);
  elvr_l.attach(ELEVATOR_L_PIN);
  elvr_r.attach(ELEVATOR_R_PIN);
  rudder.attach(RUDDER_PIN);

  startupSequence();
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
        Serial.write(packet[0]);
        Serial.write(' ');
        Serial.write(packet[1]);
        
        // Validate packet header
        if( packet[0] == 'x' || packet[0] == 'y' || packet[0] == 'z' || packet[0] == 'p')
        {
            setServos(packet[0], packet[1]);
            Serial.write('\n'); // DEBUGGING
        }
        else
        {
            Serial.println(" Packet Failed"); // DEBUGGING
        }
        pntr = 0;
      }
   }
}

void setServos(int code, int angle)
{
    if(code == 'x')
    {
       x = angle;
    }
    else if(code == 'y')
    {
        y = angle;
    }
    else if(code == 'z')
    {
        z = angle;
    }
    else if(code == 'p')
    {
        p = angle;
    }

    ailr_l.write(x);
    ailr_r.write(x);
    elvr_l.write(y);
    elvr_r.write(map(y, 0, 180, 180, 0));
    rudder.write(z);
}


void startupSequence()
{
  for( int i = 0; i < 180; i++)
  {
    ailr_l.write(i);
    ailr_r.write(i);
    elvr_l.write(i);
    elvr_r.write(i);
    rudder.write(i);
    delay(10);
  }
  
  for( int i = 180; i > 0; i--)
  {
    ailr_l.write(i);
    ailr_r.write(i);
    elvr_l.write(i);
    elvr_r.write(i);
    rudder.write(i);
    delay(10);
  }

  // Reset to level
  ailr_l.write(90);
  ailr_r.write(90);
  elvr_l.write(90);
  elvr_r.write(90);
  rudder.write(90);

  Serial.println("Startup complete");
}
