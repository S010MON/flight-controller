void setup() 
{
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(8, HIGH);
  Serial.begin(115200);
  Serial.println("Hello World");
}

void loop() 
{
    if(Serial.available())
    {
      char c = Serial.read();
      if( c == '0')
      {
        digitalWrite(13, LOW);
      }
      else if ( c == '1')
      {
        digitalWrite(13, HIGH);
      }
    }
}
