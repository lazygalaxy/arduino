/*
   Circus.ino - Example on how to use the LazyGalaxy NeoPixel library.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 8, 2018.
   Released into the public domain.
*/

#include <LazyGalaxyNeoPixel.h>

static const unsigned int DELAY = 50;

NeoPixel strip(D11, 33);

void allOff(unsigned long time) { strip.off(); }

void wipeSequenceReverse(unsigned long time) {
  strip.setWipeSequence(0.75, 1.0, 0.5, DELAY, true, allOff);
}
void wipeSequence(unsigned long time) {
  strip.setWipeSequence(0.5, 1.0, 0.5, DELAY, false, wipeSequenceReverse);
}
void chaseSequence(unsigned long time) {
  strip.setChaseSequence(0, 1.0, 0.5, DELAY, 1000, 3);
}

void allRed(unsigned long time) { strip.setNoSequence(0.00, 1.0, 0.5); }
void allGreen(unsigned long time) { strip.setNoSequence(0.33, 1.0, 0.5); }
void allBlue(unsigned long time) { strip.setNoSequence(0.66, 1.0, 0.5); }

void setup() {
  Serial.begin(9600);
  strip.setup();

  // set all LEDs to red
  Timer::scheduleTask(0, allRed);
  // schedule a task to set all LEDs to green in 2 seconds
  Timer::scheduleTask(2000, allGreen);
  // schedule a task to set all LEDs to blue in 4 seconds
  Timer::scheduleTask(4000, allBlue);
  // schedule a chase sequence in 6 seconds
  Timer::scheduleTask(6000, chaseSequence);
  // schedule a wipe sequence in 8 seconds
  Timer::scheduleTask(8000, wipeSequence);
}

void loop() {
  // update all LazyGalaxy tasks
  Timer::updateTasks();
}
