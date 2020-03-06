/*
   TimerExample.cpp - Example on the usage of the LazyGalaxyTimer util
   Created by LazyGalaxy - Evangelos Papakonstantis, March 6, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

void printHello(unsigned long time) {
  Serial.println("Hello @" + String(time));
}

void printGoodbye(unsigned long time) {
  Serial.println("Goodbye @" + String(time));
}

void setup() {
  Serial.begin(9600);

  // schedule a task to print "Hello" in 3 seconds
  LazyGalaxyTimer::scheduleTask(3000, printHello);
  // schedule a task to print "Goodbye" in 6 seconds
  LazyGalaxyTimer::scheduleTask(6000, printGoodbye);
}

void loop() {
  // update the LazyGalaxy tasks
  LazyGalaxyTimer::updateTasks();
}