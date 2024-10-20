/*
   LazyGalaxyButton.h - Library for a momentary button configured as a pullup.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYBUTTON_H
#define LAZYGALAXYBUTTON_H

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyTimer.h>

class Button : public PinComponent
{
public:
  Button(uint8_t pin);
  void setup() override;
  void reset() override;
  unsigned long update(unsigned long time) override;

  int popClickCounter();
  boolean popLongPressed();
  bool isOn();
  void setOn(bool buttonOn);

private:
  unsigned long _pressTime;
  unsigned long _releaseTime;
  int _prevValue;
  int _clickCounter;
  int _tempClickCounter;
  boolean _buttonOn;
  boolean _longPressed;
};

#endif