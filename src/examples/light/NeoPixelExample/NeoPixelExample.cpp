/*
   Example on how to use the LazyGalaxy NeoPixel library.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 8, 2018.
   Released into the public domain.
*/

#include <LazyGalaxyTimer.h>
#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyNeoPixel.h>

static const unsigned int DELAY = 50;

MyNeoPixel strip(D6, 33);

void allOff(unsigned long time) { strip.off(); }

void wipeSequenceReverse(unsigned long time)
{
  Serial.println("wipeSequenceReverse");
  strip.setWipeSequence(85, 255, 128, true, DELAY, allOff);
}

void wipeSequence(unsigned long time)
{
  strip.setWipeSequence(0, 255, 128, false, DELAY, wipeSequenceReverse);
}

void allRed(unsigned long time) { strip.setNoSequence(0, 255, 128); }
void allGreen(unsigned long time) { strip.setNoSequence(85, 255, 128); }
void allBlue(unsigned long time) { strip.setNoSequence(170, 255, 128); }

void setup()
{
  Circuit::add(&strip);
  Circuit::setup();

  // set all LEDs to red
  Timer::schedule(0, allRed);
  // schedule a task to set all LEDs to green in 2 seconds
  Timer::schedule(2000, allGreen);
  // schedule a task to set all LEDs to blue in 4 seconds
  Timer::schedule(4000, allBlue);
  // schedule a chase sequence in 6 seconds
  // Timer::schedule(6000, chaseSequence);
  // schedule a wipe sequence in 8 seconds
  Timer::schedule(6000, wipeSequence);
}

void loop()
{
  Circuit::loop();
  Timer::loop();
}
