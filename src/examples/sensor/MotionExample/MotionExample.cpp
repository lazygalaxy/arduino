/*
   MotionExample.cpp - Example for motion sensing.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 3, 2024.
   Released into the public domain.
 */

#include <LazyGalaxySystem.h>
#include <LazyGalaxyMotion.h>

void setup()
{
  Serial.begin(9600);
  Debug.setDebugLevel(DBG_DEBUG);

  System::add(new MyMotion());
  System::setup();
}

void loop()
{
  // update all LazyGalaxy tasks
  System::loop();
}