#define d0 2
#define d1 3
#define d2 4
#define d3 5
#define d4 6
#define d5 7
#define d6 8
#define d7 9

#define SELECT 12
#define ENABLE 13

int data;

void setup() 
{
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);

  pinMode(SELECT, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  Serial.begin(9600);
  Serial.println("Started");
}

void loop()
{
  for( int i = 0; i < 180; i++)
  {
    writeOut(1, i);
    delay(10); 
  }

  for( int i = 0; i < 180; i++)
  {
    writeOut(2, i);
    delay(10); 
  }
}

void writeOut(int servo, int val)
{
  digitalWrite(ENABLE, LOW);
  
  switch(servo)
  {
    case 1:
      digitalWrite(SELECT, LOW);
      break;
    case 2:
      digitalWrite(SELECT, HIGH);

      break;
  }

  int bits[8];

  bits[0] = val & 1;
  bits[1] = val & 2;
  bits[2] = val & 4;
  bits[3] = val & 8;
  bits[4] = val & 16;
  bits[5] = val & 32;
  bits[6] = val & 64;
  bits[7] = val & 128;

  digitalWrite(d0, (bits[0] > 0));
  digitalWrite(d1, (bits[1] > 0));
  digitalWrite(d2, (bits[2] > 0));
  digitalWrite(d3, (bits[3] > 0));
  digitalWrite(d4, (bits[4] > 0));
  digitalWrite(d5, (bits[5] > 0));
  digitalWrite(d6, (bits[6] > 0));
  digitalWrite(d7, (bits[7] > 0));
  
  digitalWrite(ENABLE, HIGH);
}