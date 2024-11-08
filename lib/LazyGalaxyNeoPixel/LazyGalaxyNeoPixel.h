/*
   NeoPixel.h - Library for ws2812 LED strip.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 7, 2018.
   Released into the public domain.
 */

#ifndef LAZYGALAXYNEOPIXEL_H
#define LAZYGALAXYNEOPIXEL_H

#include <FastLED.h>
#include <LazyGalaxyCommon.h>

static const unsigned char NO_SEQUENCE_TYPE = 0;
static const unsigned char WIPE_SEQUENCE_TYPE = 1;
// static const unsigned char CHASE_SEQUENCE_TYPE = 2;

class NeoPixel : public PinComponent
{
public:
  NeoPixel(char pin, int ledArraySize);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  // void setRGBColor(int pixel, uint8_t red, uint8_t gre, uint8_t blu, bool mustShow = true);
  void setHSVColor(int pixel, uint8_t hue, uint8_t sat, uint8_t val, bool mustShow = true);
  void off();
  void setWipeSequence(uint8_t hue, uint8_t sat, uint8_t val, unsigned int delay = 50, bool reverse = false, finalCallbackPtr finalCallback = nullptr);
  // void setChaseSequence(uint8_t hue, uint8_t sat, uint8_t val, unsigned int delay = 50, unsigned short cycles = 50, unsigned char gap = 3, finalCallbackPtr finalCallback = nullptr);
  void setNoSequence(uint8_t hue, uint8_t sat, uint8_t val, float probability = 1.0);

private:
  CRGB *_ledArray;
  int _ledArraySize;
  unsigned char _sequenceType;
  uint8_t _seqHue;
  uint8_t _seqSat;
  uint8_t _seqVal;
  unsigned int _sequenceDelay;
  bool _sequenceReverse;
  // int _sequenceCycles;
  // unsigned char _sequenceGap;
  int _sequenceIndex;
};

#endif
