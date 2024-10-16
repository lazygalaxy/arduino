/*
   TimerExample.cpp - Example on the usage of the LazyGalaxyTimer util
   Created by LazyGalaxy - Evangelos Papakonstantis, March 6, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

unsigned long printHello(unsigned long time)
{
  DEBUG_INFO("Hello %lu", time);
  return time;
}

unsigned long printGoodbye(unsigned long time)
{
  DEBUG_INFO("Goodbye %lu", time);
  return time;
}

void setup()
{
  Serial.begin(9600);
  Debug.setDebugLevel(DBG_VERBOSE);

  // schedule a task to print "Hello" in 3 seconds
  scheduleTask(3000, printHello);
  // schedule a task to print "Goodbye" in 6 seconds
  scheduleTask(6000, printGoodbye);
}

void loop()
{
  // update all LazyGalaxy tasks
  updateTasks();
}