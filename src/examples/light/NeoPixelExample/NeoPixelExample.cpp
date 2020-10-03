/*
   Circus.ino - Example on how to use the LazyGalaxy NeoPixel library.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 8, 2018.
   Released into the public domain.
*/

#include <LazyGalaxyNeoPixel.h>

static const unsigned int DELAY = 50;

NeoPixel strip(D11, 35);

void allOff(unsigned long time) { strip.off(); }

void allRed(unsigned long time) { strip.setSimpleSequence(0.00, 1.0, 1.0); }
void allGreen(unsigned long time) { strip.setSimpleSequence(0.33, 1.0, 1.0); }
void allBlue(unsigned long time) { strip.setSimpleSequence(0.66, 1.0, 1.0); }

void wipeSequence6(unsigned long time) {
  strip.setWipeSequence(0, 1.0, 0.0, DELAY, true, allOff);
}
void wipeSequence5(unsigned long time) {
  strip.setWipeSequence(0.75, 1.0, 1.0, DELAY, false, wipeSequence6);
}
void wipeSequence4(unsigned long time) {
  strip.setWipeSequence(0.5, 1.0, 1.0, DELAY, true, wipeSequence5);
}
void wipeSequence3(unsigned long time) {
  strip.setWipeSequence(0.25, 1.0, 1.0, DELAY, false, wipeSequence4);
}
void wipeSequence2(unsigned long time) {
  strip.setWipeSequence(0, 1.0, 1.0, DELAY, true, wipeSequence3);
}
void wipeSequence1(unsigned long time) {
  strip.setWipeSequence(0, 0.0, 1.0, DELAY, false, wipeSequence2);
}

void setup() {
  Serial.begin(9600);
  strip.setup();

  // set all LEDs to red
  Timer::scheduleTask(0, allRed);
  // schedule a task to set all LEDs to green in 2 seconds
  Timer::scheduleTask(2000, allGreen);
  // schedule a task to set all LEDs to blue in 4 seconds
  Timer::scheduleTask(4000, allBlue);
  // schedule a task to set all LEDs off in 6 seconds
  Timer::scheduleTask(6000, wipeSequence1);
}

void loop() {
  // update all LazyGalaxy tasks
  Timer::updateTasks();

  // unsigned short cycles = 10;
  // unsigned short gap = 5;
  // strip.off();
  // strip.setChaseSequence(0, 1.0, 1.0, delay, cycles, gap);
  // strip.setChaseSequence(0.25, 1.0, 1.0, delay, cycles, gap);
  // strip.setChaseSequence(0.5, 1.0, 1.0, delay, cycles, gap);
  // strip.setChaseSequence(0.75, 1.0, 1.0, delay, cycles, gap);
}
