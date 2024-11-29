/*
   MotionExample.cpp - Example for motion sensing.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 3, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyMotion.h>

MyMotion motion(1000); // A4 //A5

void motionCallback(unsigned long time, uint16_t accel, uint16_t gyro)
{
  Serial.print(accel);
  Serial.print(" ");
  Serial.println(gyro);
}

void setup()
{
  Circuit::add(&motion);
  Circuit::setup();

  motion.startCallback(motionCallback);
}

void loop()
{
  Circuit::loop();
}