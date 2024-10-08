/*
   LazyGalaxyMotion.cpp - Library for motion sensing.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 3, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyMotion.h>

MyMotion::MyMotion(unsigned long updateTime, motionCallbackPtr motionCallback) : PinComponent(255)
{
  _updateTime = updateTime;
  _motionCallback = motionCallback;
}

void MyMotion::setup()
{
  //_accelgyro.initialize();
  //_accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
  //_accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  // if (isDebug())
  //{
  //  if (_accelgyro.testConnection())
  //     Serial.println(F("MPU6050 OK"));
  //  else
  //    Serial.println(F("MPU6050 fail"));
  //}

  Timer::getInstance()->schedule(update(millis()), this);
}

unsigned long MyMotion::update(unsigned long time)
{
  //_accelgyro.getMotion6(&_ax, &_ay, &_az, &_gx, &_gy, &_gz);

  // find absolute and divide on 100
  // int gyroX = abs(_gx / 100);
  // int gyroY = abs(_gy / 100);
  // int gyroZ = abs(_gz / 100);
  // int accelX = abs(_ax / 100);
  // int accelY = abs(_ay / 100);
  // int accelZ = abs(_az / 100);

  // vector sum
  // _accel = sq((long)accelX) + sq((long)accelY) + sq((long)accelZ);
  // _accel = sqrt(_accel);
  // _gyro = sq((long)gyroX) + sq((long)gyroY) + sq((long)gyroZ);
  // _gyro = sqrt((long)_gyro);

  if (_motionCallback != nullptr)
  {
    _motionCallback(time, _accel, _gyro);
  }

  debugPrintln(String(getAccel()) + " " + String(getGyro()) + " " + String(getAx()) + " " + String(getAy()) + " " + String(getAz()) + " " + String(getGx()) + " " + String(getGy()) + " " + String(getGz()));
  return time + _updateTime;
}

int16_t MyMotion::getAx() { return _ax; }
int16_t MyMotion::getAy() { return _ay; }
int16_t MyMotion::getAz() { return _az; }
int16_t MyMotion::getGx() { return _gx; }
int16_t MyMotion::getGy() { return _gy; }
int16_t MyMotion::getGz() { return _gz; }

unsigned long MyMotion::getAccel() { return _accel; }
unsigned long MyMotion::getGyro() { return _gyro; }
