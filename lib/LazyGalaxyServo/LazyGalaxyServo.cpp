/*
   LazyGalaxyServo.h - Library for controlling a Servo
   Created by LazyGalaxy - Evangelos Papakonstantis, July 2, 2023.
   Released into the public domain.
 */

#include <LazyGalaxyServo.h>

MyServo::MyServo() : PinComponent(0) {}

MyServo::MyServo(uint8_t pin) : PinComponent(pin)
{
  _lastAngle = 90;
}

MyServo::MyServo(uint8_t pin, uint8_t angle) : PinComponent(pin)
{
  _lastAngle = angle;
}

void MyServo::setup()
{
  _servo.attach(_pin);
  setAngle(_lastAngle);
  Serial.println("setup servo on pin " + String(_pin) + " at angle " + String(_lastAngle));
}

uint8_t MyServo::setAngle(uint8_t angle)
{
  if (angle < 0)
    angle = 0;

  if (angle > 180)
    angle = 180;

  _servo.write(angle);
  uint8_t diff = abs(_lastAngle - angle);
  _lastAngle = angle;
  return diff;
}

uint8_t MyServo::addAngle(uint8_t angle)
{
  return setAngle(_lastAngle + angle);
}

uint8_t MyServo::getLastAngle()
{
  return _lastAngle;
}
