/*
   LazyGalaxyServo.h - Library for controlling a Servo
   Created by LazyGalaxy - Evangelos Papakonstantis, July 2, 2023.
   Released into the public domain.
 */

#ifndef LAZYGALAXYSERVO_H
#define LAZYGALAXYSERVO_H

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyTimer.h>
#include <Servo.h>

class MyServo : PinComponent
{

private:
  Servo _servo;
  uint8_t _lastAngle;

public:
  MyServo();
  MyServo(uint8_t pin);
  MyServo(uint8_t pin, uint8_t angle);
  void setup();
  uint8_t setAngle(uint8_t angle);
  uint8_t addAngle(uint8_t angle);
  uint8_t getLastAngle();
};

#endif
