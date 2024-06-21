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
  Button(uint8_t buttonPin, uint8_t ledPin = -1);
  int getClicks(unsigned int delay = 200);
  boolean isLongPressed(unsigned int duration);

  bool isOn();
  void setOn(bool buttonOn);

private:
  LED *led = nullptr;
  unsigned long _pressTime = 0;
  unsigned long _releaseTime = 0;
  int _prevValue = HIGH;
  int _clickCounter = 0;
  boolean _buttonOn = false;
  boolean _longPressed = false;
};

#endif