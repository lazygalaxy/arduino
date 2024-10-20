/*
   LazyGalaxyLED.h - Library for controlling a LED
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYLED_H
#define LAZYGALAXYLED_H

#include <LazyGalaxyCommon.h>

class LED : public PinComponent
{
private:
  unsigned int _blinkDelay;

public:
  LED(uint8_t pin);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void setLight(bool flag);
  bool isLight();
  void startBlink(bool flag, unsigned int blinkDelay = 500);
};

#endif
