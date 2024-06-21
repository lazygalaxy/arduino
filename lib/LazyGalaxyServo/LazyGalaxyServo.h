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
  Servo servo;
  int lastAngle;

public:
  MyServo(uint8_t pin);
  MyServo(uint8_t pin, int angle);
  int setAngle(int angle);
  int getLastAngle();
  int addAngle(int angle);
  void setup();
};

#endif
