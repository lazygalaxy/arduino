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

static const unsigned char NO_SEQUENCE = 0;
static const unsigned char CHASE_SEQUENCE = 1;
static const unsigned char WIPE_SEQUENCE = 2;

class NeoPixel : public Component {
 public:
  NeoPixel(char pin, unsigned short pixels);
  void setup();
  void setRGBColor(unsigned short pixel, float red, float green, float blue,
                   bool mustShow = true);
  void setHSVColor(unsigned short pixel, float hue, float saturation,
                   float value, bool mustShow = true);
  void off();
  void setWipeSequence(float hue, float saturation, float value,
                       unsigned int sequenceDelay = 0, bool reverse = false,
                       taskCallbackPtr finalCallback = nullptr);
  void setChaseSequence(float hue, float saturation, float value,
                        unsigned int sequenceDelay = 0,
                        unsigned short cycles = 1, unsigned short gap = 3,
                        taskCallbackPtr finalCallback = nullptr);
  void setSimpleSequence(float hue, float saturation, float value,
                         float probability = 1.0);
  void stopSequence();
  unsigned long update(unsigned long time) override;

 private:
  Adafruit_NeoPixel* _strip;
  unsigned long _sequenceTaskId = 0;
  unsigned char _sequence;
  float _sequenceHue;
  float _sequenceSaturation;
  float _sequenceValue;
  unsigned int _sequenceDelay;
  bool _sequenceReverse;
  uint16_t _sequenceCurrentIndex;
  taskCallbackPtr _finalCallback;
};

#endif
