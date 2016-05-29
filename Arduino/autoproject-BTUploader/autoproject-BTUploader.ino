void setup()
{
  Serial2.begin(38400);              
  Serial.begin(9600);                 
}

void loop()
{
  if (Serial2.available())
    Serial.write(Serial2.read());
  if (Serial.available())
    Serial2.write(Serial.read());  

}
