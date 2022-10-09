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

int l_x_new;
int l_y_new;
int r_x_new;
int r_y_new;

int delta_l_x;
int delta_l_y;
int delta_r_x;
int delta_r_y;

int sensitivity = 2;
bool led;
int flashRate = 1000; // milliseconds
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

  l_x_new = map(analogRead(L_STICK_X), 0, 1023, 0, 128);
  l_y_new = map(analogRead(L_STICK_Y), 0, 1023, 0, 128);
  r_x_new = map(analogRead(R_STICK_X), 0, 1023, 0, 128);
  r_y_new = map(analogRead(R_STICK_Y), 0, 1023, 0, 128);

  delta_l_x = abs(l_x - l_x_new);
  delta_l_y = abs(l_y - l_y_new);
  delta_r_x = abs(r_x - r_x_new);
  delta_r_y = abs(r_y - r_y_new);

  // If a change is detected in the joysticks
  if(delta_l_x > sensitivity)
  {
    l_x = l_x_new;
    HC12.write('z');
    HC12.write(l_x);
    HC12.write('\n');

    Serial.write('z');
    Serial.write(l_x);
    Serial.write('\n');
  }

  if(delta_l_y > sensitivity)
  {
    l_y = l_y_new;
    HC12.write('p');
    HC12.write(l_y);
    HC12.write('\n');

    Serial.write('p');
    Serial.write(l_y);
    Serial.write('\n');
  }

  if(delta_r_x > sensitivity)
  {
    r_x = r_x_new;
    HC12.write('x');
    HC12.write(r_x);
    HC12.write('\n');

    Serial.write('x');
    Serial.write(r_x);
    Serial.write('\n');
  }

  if(delta_r_y > sensitivity)
  {
    r_y = r_y_new;
    HC12.write('y');
    HC12.write(r_y);
    HC12.write('\n');

    Serial.write('y');
    Serial.println(r_y, DEC);
  }
}

void checkTimer()
{
  long currentTime = millis();
  long timeElapsed = currentTime - timer;
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
      timer = currentTime;
  }
}

