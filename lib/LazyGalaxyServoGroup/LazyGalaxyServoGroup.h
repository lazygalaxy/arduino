/*
   LazyGalaxyServoGroup.h - Library for controlling a group of Servos
   Created by LazyGalaxy - Evangelos Papakonstantis, June 21, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYSERVOGROUP_H
#define LAZYGALAXYSERVOGROUP_H

#include <LazyGalaxyServo.h>

class ServoGroup
{
private:
  uint8_t _total = 0;
  MyServo *_servos = nullptr;

public:
  ServoGroup(uint8_t total, uint8_t pins[]);
  ServoGroup(uint8_t total, uint8_t pins[], uint8_t angles[]);
  void setup();
  void setAngles(uint8_t angles[]);
  void addAngles(uint8_t angles[]);
};

#endif
