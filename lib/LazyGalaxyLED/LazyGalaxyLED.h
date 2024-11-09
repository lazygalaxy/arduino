/*
   LazyGalaxyLED.h - Library for controlling a LED
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYLED_H
#define LAZYGALAXYLED_H

#include <LazyGalaxyCommon.h>

class MyLED : public PinComponent
{
private:
  uint16_t _blinkDelay;

public:
  MyLED(uint8_t pin);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void setLight(bool flag, bool considerDeActivation = true);
  bool isLight();
  void startBlink(uint16_t blinkDelay = 500);
  void stopBlink();
};

#endif
