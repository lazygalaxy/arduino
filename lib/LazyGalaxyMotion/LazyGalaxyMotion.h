/*
   LazyGalaxyMotion.h - Library for motion sensing.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 3, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYMOTION_H
#define LAZYGALAXYMOTION_H

#include <LazyGalaxyCommon.h>
#include "MPU6050.h"

typedef void (*motionCallbackPtr)(unsigned long time, unsigned long accel, unsigned long gyro);

class MyMotion : public PinComponent
{
public:
  MyMotion(unsigned long updateTime = 50, motionCallbackPtr motionCallback = nullptr);
  void setup() override;
  void reset() override;
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
  int16_t _ax = 0, _ay = 0, _az = 0, _gx = 0, _gy = 0, _gz = 0;
  unsigned long _accel = 0, _gyro = 0;
  unsigned long _updateTime;
  motionCallbackPtr _motionCallback;
};

#endif
