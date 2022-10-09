#include <Servo.h>

#define AILERON_L_PIN 11
#define AILERON_R_PIN 10
#define ELEVATOR_L_PIN 9
#define ELEVATOR_R_PIN 6
#define RUDDER_PIN 5

#define d0 A0
#define d1 A1
#define d2 A2
#define d3 A3
#define d4 A4
#define d5 A5
#define d6 A6
#define d7 A7

#define SELECT_0 8
#define SELECT_1 9

Servo ailr_l;
Servo ailr_r;
Servo elvr_l;
Servo elvr_r;
Servo rudder;

int x = 90;
int y = 90;
int z = 90;
int p = 0;

int slct_0;
int slct_1;
int data;

int refreshRate = 100; // milliseconds
long timer;

void setup()
{
  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  pinMode(d7, INPUT);

  pinMode(SELECT_0, INPUT);
  pinMode(SELECT_1, INPUT);

  Serial.begin(9600);

  ailr_l.attach(AILERON_L_PIN);
  ailr_r.attach(AILERON_R_PIN);
  elvr_l.attach(ELEVATOR_L_PIN);
  elvr_r.attach(ELEVATOR_R_PIN);
  rudder.attach(RUDDER_PIN);

  startupSequence();
  timer = millis();
  Serial.println("Started");
}

void loop() 
{
  readPortIn();
  Serial.println(data);
  /*
    x = 00, y = 01, z = 10, p = 11
  */
    x = data;
    ailr_l.write(x);
    ailr_r.write(x);
  // else if(slct_1)
  // {
  //   y = data;
  //   elvr_l.write(y);
  //   elvr_r.write(y);
  // }
  // else if(false)
  // {
  //   z = data;
  //   rudder.write(z); 
  // }  
  // else
  // {
  //   p = data;
  // }  
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

void readPortIn()
{
  slct_0 = digitalRead(SELECT_0);
  slct_1 = digitalRead(SELECT_1);

  int bits[8];
  bits[0] = digitalRead(d0);
  bits[1] = digitalRead(d1);
  bits[2] = digitalRead(d2);
  bits[3] = digitalRead(d3);
  bits[4] = digitalRead(d4);
  bits[5] = digitalRead(d5);
  bits[6] = digitalRead(d6);
  bits[7] = digitalRead(d7);

  data = 0;
  for(int i = 7; i > 0; i--)
  {
    data = (data | bits[i]) << 1;
  }
  data = (data | bits[0]);
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
