#include <EduIntro.h>

Potentiometer potentiometers[] = {A0, A1, A2, A3, A4, A5};

void setup()
{
  Serial.begin(9600);
}

void writeResistancesToSerial()
{
  for (int i = 0; i < sizeof(potentiometers); i++)
  {
    Serial.write(potentiometers[i].read());
  }
}

void loop()
{
  writeResistancesToSerial();
}
