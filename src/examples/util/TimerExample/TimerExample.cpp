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
    Serial.println("Hello");
    return time + 1000;
  }
  return 0;
}

void printGoodbye(unsigned long time)
{
  Serial.println("Goodbye");
}

void printHaveANiceDay(unsigned long time)
{
  Serial.println("Have a nide day");
}

void setup()
{
  Serial.begin(115200);

  // schedule a task to print "Hello" three times in 2 seconds, then print "Goodbye"
  Timer::schedule(2000, printHello, printGoodbye);
  // schedule a task to print "Goodbye" in 6 seconds
  Timer::schedule(8000, printHaveANiceDay);
}

void loop()
{
  // update all LazyGalaxy tasks
  Timer::loop();
}