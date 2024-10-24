/*
   LazyGalaxyButton.cpp - Library for a momentary button configured as a pullup.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyButton.h>

Button::Button(uint8_t pin) : PinComponent(pin)
{
}

void Button::setup()
{
  pinMode(_pin, INPUT_PULLUP);
  _clicksCallback = nullptr;
  _longPressCallback = nullptr;
}

void Button::reset()
{
  Component::reset();
  // we are basically always active for buttons
  _triggerTime = 1;
  _pressTime = 0;
  _releaseTime = 0;
  _prevValue = HIGH;
  _clicks = 0;
  _isLongPress = false;
}

void Button::startClicksCallback(clicksCallbackPtr clicksCallback)
{
  _clicksCallback = clicksCallback;
}

void Button::stopClicksCallback()
{
  _clicksCallback = nullptr;
}

void Button::startLongPressCallback(longPressCallbackPtr longPressCallback)
{
  _longPressCallback = longPressCallback;
}

void Button::stopLongPressCallback()
{
  _longPressCallback = nullptr;
}

unsigned long Button::update(unsigned long time)
{
  int value = digitalRead(_pin);

  if (value == LOW && _pressTime == 0)
  {
    _pressTime = time;
    _releaseTime = 0;
    _prevValue = value;
  }
  else if (value == LOW && _pressTime != 0 && (time - _pressTime) >= 1000)
  {
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
      _clicks += 1;
      _releaseTime = time;
      _pressTime = 0;
      _prevValue = value;
    }
  }

  // wait for the delay to elapse, before registering the click counter
  if (_releaseTime != 0 && (time - _releaseTime) >= 200)
  {
    if (_clicksCallback != nullptr)
      _clicksCallback(time, _clicks);
    // temporary we deactivate the component, it will be reset and activated again
    return 0;
  }

  // we always return as as we keep the state of the button
  return 1;
}