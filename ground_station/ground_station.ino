#include <SoftwareSerial.h>

#define L_STICK_X A1
#define L_STICK_Y A0
#define R_STICK_X A3
#define R_STICK_Y A2
#define LED 13

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

int l_x;
int l_y;
int r_x;
int r_y;
bool led;
long flashRate = 1000; // milliseconds
unsigned long timer;

void setup() 
{
  Serial.begin(9600);
  HC12.begin(9600); 
  
  pinMode(LED, OUTPUT);
  pinMode(L_STICK_X, INPUT);
  pinMode(L_STICK_Y, INPUT);
  pinMode(R_STICK_X, INPUT);
  pinMode(R_STICK_Y, INPUT);

  for(int i = 0; i < 3; i++)
  {
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
  }

  digitalWrite(LED, HIGH);
  led = true;
  timer =  millis();
}

void loop()
{
  checkTimer();
  
  l_y = map(analogRead(L_STICK_Y), 0, 1023, 0, 180);
  r_x = map(analogRead(R_STICK_X), 0, 1023, 0, 180);
  r_y = map(analogRead(R_STICK_Y), 0, 1023, 0, 180);

  if( map(analogRead(R_STICK_X), 0, 1023, 0, 180) != r_x)         // Roll
  {
    r_x = map(analogRead(R_STICK_X), 0, 1023, 0, 180);
    HC12.write('x');
    HC12.write(r_x);
    HC12.write('\n');
  }
  else if( map(analogRead(R_STICK_Y), 0, 1023, 0, 180) != r_y)    // Pitch
  {
    r_y = map(analogRead(R_STICK_Y), 0, 1023, 0, 180);
    HC12.write('y');
    HC12.write(r_y);
    HC12.write('\n');
  }
  else if( map(analogRead(L_STICK_X), 0, 1023, 0, 180) != l_x)    // Yaw
  {
    l_x = map(analogRead(L_STICK_X), 0, 1023, 0, 180);
    HC12.write('z');
    HC12.write(l_x);
    HC12.write('\n');
  }
  else if( map(analogRead(L_STICK_Y), 0, 1023, 0, 180) != l_y)    // Power
  {
    l_y = map(analogRead(L_STICK_Y), 0, 1023, 0, 180);
    HC12.write('p');
    HC12.write(l_y);
    HC12.write('\n');
  }
}

void checkTimer()
{
  long timeElapsed = millis() - timer;
  if(timeElapsed > flashRate)
  {
      if(led)
      {
        digitalWrite(LED, LOW);
      }
      else
      {
        digitalWrite(LED, HIGH);
      }
      led = !led;
      timer = millis();
  }
}
