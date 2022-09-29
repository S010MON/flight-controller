#define SERVO_X_PIN 3
#define SERVO_Y_PIN 5
#define X_POS A0
#define Y_POS A1

#include <Servo.h>

Servo servo_x;
Servo servo_y;

int offset_x = 510;
int offset_y = 510;
int pos_x = 90;
int pos_y = 90;
float gain = 1.001;

void setup() 
{
  Serial.begin(9600);

  // Setup servo x
  servo_x.attach(SERVO_X_PIN);
  pinMode(X_POS, INPUT);

  // Setup servo y
  servo_y.attach(SERVO_Y_PIN);
  pinMode(Y_POS, INPUT);

  // Startup sequence
  for( int i = 0; i < 180; i++)
  {
    servo_x.write(i);
    servo_y.write(i);
    delay(10);
  }
  
  for( int i = 180; i > 0; i--)
  {
    servo_x.write(i);
    servo_y.write(i);
    delay(10);
  }

  // Reset to level
  servo_x.write(pos_x);
  servo_y.write(pos_y);
}

void loop() 
{
  pos_x = analogRead(X_POS);
  servo_x.write(convertToAngle(pos_x));

  pos_y = analogRead(Y_POS);
  servo_y.write(convertToAngle(pos_y));
}

/*
 * Takes an int position voltage between 0 - 1023 and converts 
 * to an angle between 0 - 180 degrees
 */
int convertToAngle(int pos)
{
  float f = pos;
  float k = 1023/2;
//  return(int) (((((f - 510)/k) * gain) * k) * 180);

  return(int) ((f/1023) * 180);
}
