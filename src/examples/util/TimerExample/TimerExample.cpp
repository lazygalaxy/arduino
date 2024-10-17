/*
   TimerExample.cpp - Example on the usage of the LazyGalaxyTimer util
   Created by LazyGalaxy - Evangelos Papakonstantis, March 6, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

char counter = 0;

unsigned long printHello(unsigned long time)
{
  if (++counter <= 3)
  {
    DEBUG_INFO("Hello %lu", time);
    return time + 1000;
  }
  return time;
}

void printGoodbye(unsigned long time)
{
  DEBUG_INFO("Goodbye %lu", time);
}

void printHaveANiceDay(unsigned long time)
{
  DEBUG_INFO("Have a nide day %lu", time);
}

void setup()
{
  Serial.begin(9600);
  Debug.setDebugLevel(DBG_DEBUG);

  // schedule a task to print "Hello" three times in 2 seconds, then print "Goodbye"
  Timer::scheduleTask(2000, printHello, printGoodbye);
  // schedule a task to print "Goodbye" in 6 seconds
  Timer::scheduleTask(8000, printHaveANiceDay);
}

void loop()
{
  // update all LazyGalaxy tasks
  Timer::updateTasks();
}