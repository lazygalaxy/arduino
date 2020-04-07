/*
   Circus.ino - Example on how to use the LazyGalaxy NeoPixel library.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 8, 2018.
   Released into the public domain.
*/

#include <LazyGalaxyNeoPixel.h>

NeoPixel strip(D11, 35);

void setup() {
  Serial.begin(9600);
  strip.setup();
}

void loop() {
  strip.off();
  strip.noSequence(0.0, 0.0, 1.0, 1000);
  strip.noSequence(0.0, 1.0, 1.0, 1000);
  strip.noSequence(0.2, 1.0, 1.0, 1000);
  strip.noSequence(0.4, 1.0, 1.0, 1000);
  strip.noSequence(0.6, 1.0, 1.0, 1000);
  strip.noSequence(0.8, 1.0, 1.0, 1000);

  unsigned long delay = 50;

  strip.off();
  strip.wipeSequence(0, 0.0, 1.0, delay);
  strip.wipeSequence(0, 1.0, 1.0, delay, true);
  strip.wipeSequence(0.25, 1.0, 1.0, delay);
  strip.wipeSequence(0.5, 1.0, 1.0, delay, true);
  strip.wipeSequence(0.75, 1.0, 1.0, delay);
  strip.wipeSequence(0, 1.0, 0.0, delay, true);

  unsigned short cycles = 10;
  unsigned short gap = 5;
  strip.off();
  strip.chaseSequence(0, 1.0, 1.0, delay, cycles, gap);
  strip.chaseSequence(0.25, 1.0, 1.0, delay, cycles, gap);
  strip.chaseSequence(0.5, 1.0, 1.0, delay, cycles, gap);
  strip.chaseSequence(0.75, 1.0, 1.0, delay, cycles, gap);
}
