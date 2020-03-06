/*
   LazyGalaxyLED.h - Library for controlling an LED
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYLED_h
#define LAZYGALAXYLED_h

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyTimer.h>

class LazyGalaxyLED : public LazyGalaxyComponent {
 public:
  LazyGalaxyLED(uint8_t pin);
  void setLight(bool flag);
  bool isLight();
  void setBlink(bool flag, unsigned int blinkDelay = 500);
  bool isBlink();
  unsigned int update(unsigned long time);

 private:
  unsigned long _blinkTaskId = 0;
  unsigned int _blinkDelay = 0;
};

#endif
