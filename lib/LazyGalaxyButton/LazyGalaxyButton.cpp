/*
   LazyGalaxyButton.cpp - Library for a momentary button configured as a pullup.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyButton.h>

Button::Button(uint8_t pin, longPressCallbackPtr longPressCallback) : PinComponent(pin)
{
  _clickCounter = 0;
  _longPressCallback = longPressCallback;
}

void Button::setup()
{
  pinMode(_pin, INPUT_PULLUP);
}

void Button::reset()
{
  DEBUG_DEBUG("reset button");
  Component::reset();
  // we always need to check the button status
  _triggerTime = 1;
  _pressTime = 0;
  _releaseTime = 0;
  _prevValue = HIGH;
  _tempClickCounter = 0;
  _isLongPress = false;
}

int Button::popClickCounter()
{
  if (_clickCounter > 0)
  {
    int temp = _clickCounter;
    _clickCounter = 0;
    return temp;
  }
  return 0;
}

unsigned long Button::update(unsigned long time)
{
  int value = digitalRead(_pin);

  if (value == LOW && _pressTime == 0)
  {
    _pressTime = time;
    _releaseTime = 0;
    _prevValue = value;
    DEBUG_DEBUG("button pressed first time %lu", time);
  }
  else if (value == LOW && _pressTime != 0 && (time - _pressTime) >= 1000)
  {
    DEBUG_DEBUG("button registered log press at %lu", time);
    _isLongPress = true;
    if (_longPressCallback != nullptr)
      _longPressCallback(time);
  }
  else if (value == HIGH && _prevValue == LOW)
  {
    if (_isLongPress)
      return 0;
    else
    {
      _tempClickCounter += 1;
      _releaseTime = time;
      _pressTime = 0;
      _prevValue = value;
      DEBUG_DEBUG("button pressed %i clicks at %lu", _tempClickCounter, time);
    }
  }

  // wait for the delay to elapse, before registering the click counter
  if (_releaseTime != 0 && (time - _releaseTime) >= 200)
  {
    _clickCounter = _tempClickCounter;
    DEBUG_DEBUG("button registered %i clicks at %lu", _clickCounter, time);
    // temporary we deactivate the component, it will be reste and activated again
    return 0;
  }

  // we always need to check the button status
  return 1;
}