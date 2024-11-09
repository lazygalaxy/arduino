/*
   NeoPixel.h - Library for ws2812 LED strip.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 7, 2018.
   Released into the public domain.
 */

#ifndef LAZYGALAXYNEOPIXEL_H
#define LAZYGALAXYNEOPIXEL_H

#include <FastLED.h>
#include <LazyGalaxyCommon.h>

class NeoPixel : public PinComponent
{
public:
  NeoPixel(char pin, uint8_t ledArraySize);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  // void setRGBColor(int pixel, uint8_t red, uint8_t gre, uint8_t blu, bool mustShow = true);
  void setHSVColor(uint8_t ledIndex, uint8_t hue, uint8_t sat, uint8_t val, bool mustShow = true);
  void off();
  void setWipeSequence(uint8_t hue, uint8_t sat = SAT_DEFAULT, uint8_t val = VAL_DEFAULT, bool reverse = false, uint16_t delay = 15, finalCallbackPtr finalCallback = nullptr);
  // void setChaseSequence(uint8_t hue, uint8_t sat, uint8_t val, uint16_t delay = 50, uint8_t cycles = 50, uint8_t gap = 3, finalCallbackPtr finalCallback = nullptr);
  void setNoSequence(uint8_t hue, uint8_t sat = SAT_DEFAULT, uint8_t val = VAL_DEFAULT, uint8_t probability = 100);

private:
  static const uint8_t SAT_DEFAULT = 255;
  static const uint8_t VAL_DEFAULT = 128;

  static const uint8_t NO_SEQUENCE_TYPE = 0;
  static const uint8_t WIPE_SEQUENCE_TYPE = 1;
  // static const uint8_t CHASE_SEQUENCE_TYPE = 2;

  CRGB *_ledArray;
  uint8_t _ledArraySize;
  uint8_t _sequenceType;
  uint8_t _seqHue;
  uint8_t _seqSat;
  uint8_t _seqVal;
  uint16_t _sequenceDelay;
  bool _sequenceReverse;
  // int _sequenceCycles;
  // uint8_t _sequenceGap;
  uint8_t _sequenceIndex;
};

#endif
