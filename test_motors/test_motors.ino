#include <EduIntro.h>

//shield1
int pwmBase = 3;
int dirBase = 2;
int pwmShoulder = 9;
int dirShoulder = 8;

//shield2
int pwmElbow = 5;
int dirElbow = 4;
int pwmRotateElbow = 10;
int dirRotateElbow = 12;

//shield3
int pwmWrist = 6;
int dirWrist = 7;
int pwmHand = 11;
int dirHand = 13;

int pwms[] = {pwmBase, pwmShoulder, pwmElbow, pwmRotateElbow, pwmWrist, pwmHand};
int dirs[] = {dirBase, dirShoulder, dirElbow, dirRotateElbow, dirWrist, dirHand};
Potentiometer potentiometers[] = {A0, A1, A2, A3, A4, A5};
float limits[6][2] = {{1,4},{1,4},{1,4},{1,4},{1,4},{1,4}};

void moveMultiSpeed(int direction, int speeds[])
{
  for (int i = 0; i < sizeof(speeds); i++)
  {
    move(direction, speeds[i]);
    delay(1000);
  }
}

void move(int direction, int speed)
{
  for (int i = 0; i < sizeof(dirs); i++)
  {
    digitalWrite(dirs[i], direction);
  }
  for (int i = 0; sizeof(pwms); i++)
  {
    analogWrite(pwms[i], speed);
  }
}

void setup()
{
  for (int i = 0; i < sizeof(pwms); i++)
  {
    pinMode(pwms[i], OUTPUT);
    analogWrite(pwms[i], 100);
  }
  Serial.begin(9600);
}

void printAngles()
{
  for (int i = 0; i < sizeof(potentiometers); i++)
  {
    Serial.println(
        "Motor " + String(i) + ": " +
        getAngle(potentiometers[i]) +
        "π rad");
  }
}

float getAngle(Potentiometer potentiometer)
{
  return float(potentiometer.read()) / 128.0;
}

void loop()
{
  int speeds[] = {50, 0, 150, 0, 255, 0};
  moveMultiSpeed(LOW, speeds);
  delay(2000);
  moveMultiSpeed(HIGH, speeds);
  delay(2000);
}
