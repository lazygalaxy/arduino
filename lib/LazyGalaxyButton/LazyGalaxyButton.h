/*
   LazyGalaxyButton.h - Library for a momentary button configured as a pullup.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYBUTTON_H
#define LAZYGALAXYBUTTON_H

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyTimer.h>

typedef void (*clicksCallbackPtr)(unsigned long time, uint8_t clicks);
typedef void (*longPressCallbackPtr)(unsigned long time);

class MyButton : public PinComponent
{
public:
  MyButton(uint8_t pin);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void startClicksCallback(clicksCallbackPtr clicksCallback);
  void stopClicksCallback();
  void startLongPressCallback(longPressCallbackPtr longPressCallback, uint16_t longPressCallbackCycle = 100, uint16_t longPressDuration = 1000);
  void stopLongPressCallback();

private:
  unsigned long _pressTime;
  unsigned long _releaseTime;
  bool _isLongPressed;
  uint8_t _clicks;
  clicksCallbackPtr _clicksCallback;
  longPressCallbackPtr _longPressCallback;
  uint16_t _longPressCallbackCycle;
  uint16_t _longPressDuration;
};

#endif