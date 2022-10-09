#include <Servo.h>

#define AILERON_L_PIN 11
#define AILERON_R_PIN 10
#define ELEVATOR_L_PIN 9
#define ELEVATOR_R_PIN 6
#define RUDDER_PIN 5
#define AILERON_L_IN A0

Servo ailr_l;
Servo ailr_r;
Servo elvr_l;
Servo elvr_r;
Servo rudder;

int x = 90;
int y = 90;
int z = 90;
int p = 0;

int refreshRate = 100; // milliseconds
long timer;

void setup()
{
  Serial.begin(9600);

  ailr_l.attach(AILERON_L_PIN);
  ailr_r.attach(AILERON_R_PIN);
  elvr_l.attach(ELEVATOR_L_PIN);
  elvr_r.attach(ELEVATOR_R_PIN);
  rudder.attach(RUDDER_PIN);

  startupSequence();
  timer = millis();
}

void loop() 
{
    if(Serial.available())
    {
      int data = Serial.read();
      Serial.print(data);
      x = map(data, 0, 255, 0, 180);      
    }

    if(checkTimer())
    {
      ailr_l.write(x);
      ailr_r.write(x);
      elvr_l.write(y);
      elvr_r.write(map(y, 0, 180, 180, 0));
      rudder.write(z);      
    }
}


bool checkTimer()
{
  long currentTime = millis();
  long timeElapsed = currentTime - timer;
  if(timeElapsed > refreshRate)
  {
    timer = currentTime;
    return true;
  }
  return false;
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
