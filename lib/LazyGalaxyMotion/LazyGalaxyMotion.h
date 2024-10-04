/*
   LazyGalaxyMotion.h - Library for motion sensing.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 3, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYMOTION_H
#define LAZYGALAXYMOTION_H

#include <LazyGalaxyTimer.h>
#include <LazyGalaxyCommon.h>
#include "MPU6050.h"

class MyMotion : public PinComponent
{
public:
  MyMotion();
  void setup() override;
  unsigned long update(unsigned long time) override;
  int16_t getAx();
  int16_t getAy();
  int16_t getAz();
  int16_t getGx();
  int16_t getGy();
  int16_t getGz();
  unsigned long getAccel();
  unsigned long getGyro();

private:
  MPU6050 _accelgyro;
  int16_t _ax, _ay, _az, _gx, _gy, _gz;
  unsigned long _accel, _gyro;
};

#endif
