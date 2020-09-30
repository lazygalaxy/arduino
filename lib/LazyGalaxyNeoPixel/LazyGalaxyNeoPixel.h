/*
   NeoPixel.h - Library for ws2812 LED strip.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 7, 2018.
   Released into the public domain.
 */

#ifndef LAZYGALAXYNEOPIXEL_H
#define LAZYGALAXYNEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include <LazyGalaxyCommon.h>
#include <LazyGalaxyTimer.h>

class NeoPixel : public Component {
 public:
  NeoPixel(char pin, unsigned short pixels);
  void setup();
  void setRGBColor(unsigned short pixel, float red, float green, float blue,
                   bool mustShow = true);
  void setHSVColor(unsigned short pixel, float hue, float saturation,
                   float value, bool mustShow = true);
  void off();
  void wipeSequence(float hue, float saturation, float value,
                    unsigned long delayMicros = 0, bool reverse = false);
  void chaseSequence(float hue, float saturation, float value,
                     unsigned long delayMicros = 0, unsigned short cycles = 1,
                     unsigned short gap = 3);
  void noSequence(float hue, float saturation, float value);

 private:
  Adafruit_NeoPixel* _strip;
  unsigned int _delay = 0;
};

#endif
