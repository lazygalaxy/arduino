/*
   Circus.ino - Example on how to use the LazyGalaxy NeoPixel library.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 8, 2018.
   Released into the public domain.
*/

#include <LazyGalaxyNeoPixel.h>

NeoPixel strip(D11, 35);

void allRed() { strip.noSequence(0.00, 1.0, 1.0); }
void allGreen(unsigned long time) { strip.noSequence(0.33, 1.0, 1.0); }
void allBlue(unsigned long time) { strip.noSequence(0.66, 1.0, 1.0); }
void allOff(unsigned long time) { strip.off(); }

void setup() {
  Serial.begin(9600);
  strip.setup();

  // set all LEDs to red
  allRed();
  // schedule a task to set all LEDs to green in 3 seconds
  Timer::scheduleTask(3000, allGreen);
  // schedule a task to set all LEDs to blue in 6 seconds
  Timer::scheduleTask(6000, allBlue);
  // schedule a task to set all LEDs off in 9 seconds
  Timer::scheduleTask(9000, allOff);
}

void loop() {
  // update all LazyGalaxy tasks
  Timer::updateTasks();

  // unsigned long delay = 50;

  // strip.off();
  // strip.wipeSequence(0, 0.0, 1.0, delay);
  // strip.wipeSequence(0, 1.0, 1.0, delay, true);
  // strip.wipeSequence(0.25, 1.0, 1.0, delay);
  // strip.wipeSequence(0.5, 1.0, 1.0, delay, true);
  // strip.wipeSequence(0.75, 1.0, 1.0, delay);
  // strip.wipeSequence(0, 1.0, 0.0, delay, true);

  // unsigned short cycles = 10;
  // unsigned short gap = 5;
  // strip.off();
  // strip.chaseSequence(0, 1.0, 1.0, delay, cycles, gap);
  // strip.chaseSequence(0.25, 1.0, 1.0, delay, cycles, gap);
  // strip.chaseSequence(0.5, 1.0, 1.0, delay, cycles, gap);
  // strip.chaseSequence(0.75, 1.0, 1.0, delay, cycles, gap);
}
