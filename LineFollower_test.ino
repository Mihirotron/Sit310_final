#include <Wire.h>
#include <ZumoShield.h>

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

void setup()
{
  reflectanceSensors.init();

  button.waitForButton();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  delay(1000);
  int i;
  for (i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
    reflectanceSensors.calibrate();
    delay(30);
  }
  motors.setSpeeds(0, 0);

  digitalWrite(13, LOW);
  Serial.begin(9600); //normal printing

  button.waitForButton();
}

void loop()
{
  unsigned int sensors[6];
  
  int position = reflectanceSensors.readLine(sensors);

  if (position < 1000)
  {
    // Too far to the left of the line: turn right.
    motors.setSpeeds(0, 150);
  }
  else if (position < 3000)
  {
    // drive straight.
    motors.setSpeeds(150, 150);
  }
  else
  {
    // Too far to the left of the line: turn right.
    motors.setSpeeds(150, 0);
  }
}
