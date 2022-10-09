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

#define d0 A7
#define d1 A6
#define d2 A5
#define d3 A4
#define d4 A3
#define d5 A2
#define d6 A1
#define d7 A0

#define SELECT_1 12
#define SELECT_2 13
#define ENABLE 9

SoftwareSerial HC12(10, 11);  // HC-12 TX Pin, HC-12 RX Pin

int x = 90;
int y = 90;
int z = 90;
int p = 0;

int pntr = 0;
int packet[5];

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

  pinMode(SELECT_1, OUTPUT);
  pinMode(SELECT_2, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  Serial.begin(9600);
  HC12.begin(9600);
}

void loop()
{
  if (HC12.available())
  {
    char currentChar = HC12.read();
  
    if (currentChar != '\n')
    {
      packet[pntr++] = currentChar;
      currentChar = HC12.read();
    }
    else 
    {
      // DEBUGGING
      char header = packet[0];
      debug(header);
      debug(" ");
      debug(packet[1]);

      // Validate packet header
      if (header != 'x' && header != 'y' && header != 'z' && header != 'p')
      {
        debugln(" Packet failed");
      }
      else if (packet[0] == 'x')
      {
        x = map(packet[1], 0, 128, 0 ,179);
        writeOut(1, x);
        Serial.print("x ");
        Serial.println(x);
      }
      else if (packet[0] == 'y') 
      {
        y = map(packet[1], 0, 128, 0 ,179);
        writeOut(2, y);
        Serial.print("y ");
        Serial.println(y);
      }
      else if (packet[0] == 'z') 
      {
        z = map(packet[1], 0, 128, 0 ,179);
        writeOut(3, z);
        Serial.print("z ");
        Serial.println(z);
      }
      else if (packet[0] == 'p')
      {
        // TODO control power
      }
      pntr = 0;
    }
  }
}

void writeOut(int servo, int val)
{
  digitalWrite(ENABLE, LOW);
  
  switch(servo)
  {
    case 1:
      digitalWrite(SELECT_1, LOW);
      digitalWrite(SELECT_2, LOW);
      break;
    case 2:
      digitalWrite(SELECT_1, LOW);
      digitalWrite(SELECT_2, HIGH);
      break;
    case 3:
      digitalWrite(SELECT_1, HIGH);
      digitalWrite(SELECT_2, LOW);
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