/*
   LazyGalaxyButton.h - Library for a momentary button configured as a pullup.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYBUTTON_H
#define LAZYGALAXYBUTTON_H

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyTimer.h>

typedef void (*clicksCallbackPtr)(unsigned long time, int clicks);
typedef void (*longPressCallbackPtr)(unsigned long time);

class Button : public PinComponent
{
public:
  Button(uint8_t pin);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  void startClicksCallback(clicksCallbackPtr clicksCallback);
  void stopClicksCallback();
  void startLongPressCallback(longPressCallbackPtr longPressCallback, unsigned long longPressCallbackCycle = 100, unsigned long longPressDuration = 1000);
  void stopLongPressCallback();

private:
  unsigned long _pressTime;
  unsigned long _releaseTime;
  int _prevValue;
  int _clicks;
  bool _isLongPress;
  clicksCallbackPtr _clicksCallback;
  longPressCallbackPtr _longPressCallback;
  unsigned long _longPressCallbackCycle;
  unsigned long _longPressDuration;
};

#endif