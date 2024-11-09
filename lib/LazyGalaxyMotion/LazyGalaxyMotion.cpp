/*
   LazyGalaxyMotion.cpp - Library for motion sensing.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 3, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyMotion.h>

MyMotion::MyMotion(unsigned long updateTime) : Component()
{
  _updateTime = updateTime;
}

void MyMotion::setup()
{
  Wire.begin();
  _accelgyro.initialize();
  _accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
  _accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  if (!_accelgyro.testConnection())
    _statusOK = false;
}

void MyMotion::reset()
{
  Component::reset();
  _motionCallback = nullptr;
}

void MyMotion::startCallback(motionCallbackPtr motionCallback)
{
  _motionCallback = motionCallback;
  _triggerTime = update(millis());
}

void MyMotion::stopCallback()
{
  reset();
}

unsigned long MyMotion::update(unsigned long time)
{
  _accelgyro.getMotion6(&_ax, &_ay, &_az, &_gx, &_gy, &_gz);

  // find absolute and divide on 100
  uint16_t gyroX = abs(_gx / 100);
  uint16_t gyroY = abs(_gy / 100);
  uint16_t gyroZ = abs(_gz / 100);
  uint16_t accelX = abs(_ax / 100);
  uint16_t accelY = abs(_ay / 100);
  uint16_t accelZ = abs(_az / 100);

  // vector sum
  uint16_t _accel = sq(accelX) + sq(accelY) + sq(accelZ);
  _accel = sqrt(_accel);
  uint16_t _gyro = sq(gyroX) + sq(gyroY) + sq(gyroZ);
  _gyro = sqrt(_gyro);

  if (_motionCallback != nullptr)
    _motionCallback(time, _accel, _gyro);

  return time + _updateTime;
}
