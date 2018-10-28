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


void actuate(byte motorIndex, boolean direction, int speed)
{
  digitalWrite(dirs[motorIndex], direction);
  analogWrite(pwms[motorIndex], speed);
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


/**
 * protocol:
 *  the first byte is for selection motor and direction.
 *    0 for motor 0 LOW, 1 for motor 1 HIGH etc.
 *  the secocond byte is for the pulse width. 0 to 255.
 */
void loop()
{
  boolean isFirstByte = true;
  byte motor = 0;
  boolean direction = 0;
  byte pulseWidth = 0;
  if (Serial.available() == 0) {
    return;
  }

  if(isFirstByte){
    byte motorAndDirection = Serial.read();
    direction = motorAndDirection % 2;
    motor = motorAndDirection / 2;
    isFirstByte = false;
    return;
  }
  
  pulseWidth = Serial.read();
  actuate(motor, direction, pulseWidth);
  isFirstByte = true;
}
