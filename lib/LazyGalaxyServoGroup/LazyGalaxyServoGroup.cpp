/*
   LazyGalaxyServo.h - Library for controlling a Servo
   Created by LazyGalaxy - Evangelos Papakonstantis, July 2, 2023.
   Released into the public domain.
 */

#include <LazyGalaxyServoGroup.h>

ServoGroup::ServoGroup(uint8_t total, uint8_t pins[])
{
  _total = total;
  _servos = new MyServo[_total];
  // for (int i = 0; i < _total; i++)
  //  _servos[i] = MyServo(pins[i]);
}

ServoGroup::ServoGroup(uint8_t total, uint8_t pins[], uint8_t angles[])
{
  _total = total;
  _servos = new MyServo[_total];
  for (int i = 0; i < _total; i++)
    _servos[i] = MyServo(pins[i], angles[i]);
}

void ServoGroup::setup()
{
  for (int i = 0; i < _total; i++)
    _servos[i].setup();
  delay(1000);
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
