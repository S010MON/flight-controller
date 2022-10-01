#define L_STICK_X A1
#define L_STICK_Y A0
#define R_STICK_X A3
#define R_STICK_Y A2

int l_x;
int l_y;
int r_x;
int r_y;


void setup() 
{
  Serial.begin(9600);

  pinMode(L_STICK_X, INPUT);
  pinMode(L_STICK_Y, INPUT);
  pinMode(R_STICK_X, INPUT);
  pinMode(R_STICK_Y, INPUT);

}

void loop()
{
  l_y = map(analogRead(L_STICK_Y), 0, 1023, 0, 180);
  r_x = map(analogRead(R_STICK_X), 0, 1023, 0, 180);
  r_y = map(analogRead(R_STICK_Y), 0, 1023, 0, 180);

  if( map(analogRead(R_STICK_X), 0, 1023, 0, 180) != r_x)         // Roll
  {
    r_x = map(analogRead(R_STICK_X), 0, 1023, 0, 180);
    Serial.write('x');
    Serial.write(r_x);
    Serial.write('\n');
  }
  else if( map(analogRead(R_STICK_Y), 0, 1023, 0, 180) != r_y)    // Pitch
  {
    r_y = map(analogRead(R_STICK_Y), 0, 1023, 0, 180);
    Serial.write('y');
    Serial.write(r_y);
    Serial.write('\n');
  }
  else if( map(analogRead(L_STICK_X), 0, 1023, 0, 180) != l_x)    // Yaw
  {
    l_x = map(analogRead(L_STICK_X), 0, 1023, 0, 180);
    Serial.write('z');
    Serial.write(l_x);
    Serial.write('\n');
  }
  else if( map(analogRead(L_STICK_Y), 0, 1023, 0, 180) != l_y)    // Power
  {
    l_y = map(analogRead(L_STICK_Y), 0, 1023, 0, 180);
    Serial.write('p');
    Serial.write(l_y);
    Serial.write('\n');
  }
}
