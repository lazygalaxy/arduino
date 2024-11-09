/*
   LazyGalaxyButton.cpp - Library for a momentary button configured as a pullup.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyButton.h>

MyButton::MyButton(uint8_t pin) : PinComponent(pin)
{
}

void MyButton::setup()
{
  pinMode(_pin, INPUT_PULLUP);
  stopClicksCallback();
  stopLongPressCallback();
}

void MyButton::reset()
{
  Component::reset();
  // we are basically always active for buttons
  _triggerTime = 1;
  _pressTime = 0;
  _releaseTime = 0;
  _isLongPressed = false;
  _clicks = 0;
}

void MyButton::startClicksCallback(clicksCallbackPtr clicksCallback)
{
  _clicksCallback = clicksCallback;
}

void MyButton::stopClicksCallback()
{
  _clicksCallback = nullptr;
}

void MyButton::startLongPressCallback(longPressCallbackPtr longPressCallback, uint16_t longPressCallbackCycle, uint16_t longPressDuration)
{
  _longPressCallback = longPressCallback;
  _longPressCallbackCycle = longPressCallbackCycle;
  _longPressDuration = longPressDuration;
}

void MyButton::stopLongPressCallback()
{
  _longPressCallback = nullptr;
  _longPressCallbackCycle = 0;
  _longPressDuration = 0;
}

unsigned long MyButton::update(unsigned long time)
{
  int value = digitalRead(_pin);

  if (value == LOW && _pressTime == 0)
  {
    _pressTime = time;
    _releaseTime = 0;
  }
  else if ((value == LOW) && (((_pressTime != 0 && _longPressDuration != 0) && ((time - _pressTime) >= _longPressDuration)) || _isLongPressed))
  {
    _isLongPressed = true;
    if (_longPressCallback != nullptr && ((time - _pressTime) >= _longPressCallbackCycle))
    {
      _longPressCallback(time);
      _pressTime = time;
    }
  }
  else if (value == HIGH && _pressTime > 0)
  {
    if (_isLongPressed)
      return 0;
    else
    {
      _clicks += 1;
      _releaseTime = time;
      _pressTime = 0;
    }
  }

  // wait for the delay to elapse, before registering the click counter
  if (_releaseTime != 0 && (time - _releaseTime) >= 200)
  {
    if (_clicksCallback != nullptr)
      _clicksCallback(time, _clicks);
    return 0;
  }

  // we always return as as we keep the state of the button
  return 1;
}