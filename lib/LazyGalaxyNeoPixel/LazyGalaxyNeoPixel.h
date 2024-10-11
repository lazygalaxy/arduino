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

static const unsigned char NO_SEQUENCE_TYPE = 0;
static const unsigned char CHASE_SEQUENCE_TYPE = 1;
static const unsigned char WIPE_SEQUENCE_TYPE = 2;

class NeoPixel : public PinComponent
{
public:
  NeoPixel(char pin, unsigned short pixels);
  void setup();
  void setRGBColor(unsigned short pixel, float red, float green, float blue,
                   bool mustShow = true);
  void setHSVColor(unsigned short pixel, float hue, float saturation,
                   float value, bool mustShow = true);
  void off();
  void setWipeSequence(float hue, float saturation, float value,
                       unsigned int delay = 50, bool reverse = false,
                       finalCallbackPtr finalCallback = nullptr);
  void setChaseSequence(float hue, float saturation, float value,
                        unsigned int delay = 50, unsigned short cycles = 50,
                        unsigned char gap = 3,
                        finalCallbackPtr finalCallback = nullptr);
  void setNoSequence(float hue, float saturation, float value,
                     float probability = 1.0);
  void stopSequence();
  unsigned long update(unsigned long time) override;

private:
  Adafruit_NeoPixel *_strip;

  unsigned long _sequenceTaskId;
  unsigned char _sequenceType;
  float _sequenceHue;
  float _sequenceSaturation;
  float _sequenceValue;
  unsigned int _sequenceDelay;
  bool _sequenceReverse;
  unsigned short _sequenceCycles;
  unsigned char _sequenceGap;
  uint16_t _sequenceIndex;
};

#endif
