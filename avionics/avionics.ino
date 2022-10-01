#define AILERON_L_PIN 11
#define AILERON_R_PIN 10
#define ELEVATOR_L_PIN 9
#define ELEVATOR_R_PIN 6
#define RUDDER_PIN 5

#include <Servo.h>

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

  ailr_l.attach(AILERON_L_PIN);
  ailr_r.attach(AILERON_R_PIN);
  elvr_l.attach(ELEVATOR_L_PIN);
  elvr_r.attach(ELEVATOR_R_PIN);
  rudder.attach(RUDDER_PIN);

  // Startup sequence
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
}

void loop() 
{
   if(Serial.available())
   {
      int currentChar = Serial.read();
      if(currentChar != '\n')
      {
        packet[pntr++] = currentChar;
        currentChar = Serial.read();
      }
      else
      {
        // Validate packet
        if( packet[0] == 'x' || packet[0] == 'y' || packet[0] == 'z' || packet[0] == 'p')
        {
            setServos(packet[0], packet[1]);
            Serial.write(packet[0]);
            Serial.write(' ');
            int data = packet[1];
            Serial.print(data);
            Serial.write('\n');
        }
        else
        {
            Serial.write(packet[0]);
            Serial.write(' ');
            int data = packet[1];
            Serial.print(data);
            Serial.write(' ');
            Serial.println("Packet Failed");
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