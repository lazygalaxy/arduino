/*
   LazyGalaxyServo.h - Library for controlling a Servo
   Created by LazyGalaxy - Evangelos Papakonstantis, July 2, 2023.
   Released into the public domain.
 */

#include <LazyGalaxyServo.h>

MyServo::MyServo(uint8_t pin) : PinComponent(pin)
{
  lastAngle = 90;
}

MyServo::MyServo(uint8_t pin, int angle) : PinComponent(pin)
{
  lastAngle = angle;
}

int MyServo::setAngle(int angle)
{
  if (angle < 0)
    angle = 0;

  if (angle > 180)
    angle = 180;

  servo.write(angle);
  delay(abs(lastAngle - angle) * 3);
  lastAngle = angle;
  return lastAngle;
}

int MyServo::getLastAngle()
{
  return lastAngle;
}

int MyServo::addAngle(int angle)
{
  return setAngle(lastAngle + angle);
}

void MyServo::setup()
{
  servo.attach(_pin);
  setAngle(lastAngle);
}
