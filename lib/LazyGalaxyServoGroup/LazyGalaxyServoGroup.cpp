/*
   LazyGalaxyServo.h - Library for controlling a Servo
   Created by LazyGalaxy - Evangelos Papakonstantis, July 2, 2023.
   Released into the public domain.
 */

#include <LazyGalaxyServoGroup.h>

ServoGroup::ServoGroup(uint8_t pin1, uint8_t pin2, uint8_t pin3)
{
  _total = 3;
  _servos = new MyServo[_total];
  _servos[0] = MyServo(pin1);
  _servos[1] = MyServo(pin2);
  _servos[2] = MyServo(pin3);
}

void ServoGroup::setup()
{
  for (int i = 0; i < _total; i++)
    _servos[i].setup();
}

void ServoGroup::setAngles(uint8_t angles[])
{
  uint8_t maxDiffAngle = 0;
  for (int i = 0; i < _total; i++)
  {
    uint8_t newDiffAngle = _servos[i].setAngle(angles[i]);
    if (newDiffAngle > maxDiffAngle)
      maxDiffAngle = newDiffAngle;
  }

  delay(maxDiffAngle * 3);
}

void ServoGroup::addAngles(uint8_t angles[])
{
  uint8_t maxDiffAngle = 0;
  for (int i = 0; i < _total; i++)
  {
    uint8_t newDiffAngle = _servos[i].addAngle(angles[i]);
    if (newDiffAngle > maxDiffAngle)
      maxDiffAngle = newDiffAngle;
  }

  delay(maxDiffAngle * 3);
}
