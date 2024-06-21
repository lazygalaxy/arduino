/*
   LazyGalaxyMotorDriver.h - Library for a L298N dual motor driver.
   Created by LazyGalaxy - Evangelos Papakonstantis, May 5th, 2023.
   Released into the public domain.
 */

#ifndef LAZYGALAXYMOTORDRIVER_H
#define LAZYGALAXYMOTORDRIVER_H

#include <LazyGalaxyCommon.h>

class MotorDriver : public Component
{
public:
  MotorDriver(uint8_t enA, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enB);
  void setSpeed(int speed);
  void setForward();

private:
  PinComponent *_enA;
  PinComponent *_in1;
  PinComponent *_in2;
  PinComponent *_in3;
  PinComponent *_in4;
  PinComponent *_enB;
};

#endif
