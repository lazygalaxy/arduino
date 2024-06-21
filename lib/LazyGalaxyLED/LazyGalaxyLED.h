/*
   LazyGalaxyLED.h - Library for controlling a LED
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYLED_H
#define LAZYGALAXYLED_H

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyTimer.h>

class LED : public PinComponent
{
private:
  unsigned long _blinkTaskId = 0;
  unsigned int _blinkDelay = 0;

public:
  LED(uint8_t pin);
  void setLight(bool flag);
  bool isLight();
  void setBlink(bool flag, unsigned int blinkDelay = 500);
  bool isBlink();
  unsigned long getBlinkTaskId();
  unsigned long update(unsigned long time) override;
};

#endif
