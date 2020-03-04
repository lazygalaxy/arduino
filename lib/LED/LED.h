/*
   LED.h - Library for lighting a LED.
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#ifndef LED_h
#define LED_h

#include <Arduino.h>
#include <Component.h>
#include <Timer.h>

class LED : public Component {
 public:
  LED(uint8_t pin);
  void setLight(bool flag);
  bool isLight();
  void setBlink(bool flag, unsigned int blinkDelay = 500);
  bool isBlink();
  unsigned int update(unsigned long time);

 private:
  bool isDigital();
  uint8_t _pin;
  unsigned long _blinkTaskId = 0;
  unsigned int _blinkDelay = 0;
};

#endif
