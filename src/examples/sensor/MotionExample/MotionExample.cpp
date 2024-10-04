/*
   MotionExample.cpp - Example for motion sensing.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 3, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>
#include <LazyGalaxyMotion.h>

MyMotion motion;

void setup()
{
  Serial.begin(9600);
  motion.enableDebug();
  motion.setup();
}

void loop()
{
  // update all LazyGalaxy tasks
  Timer::updateTasks();
}