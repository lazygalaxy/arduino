/*
   LazyGalaxyButton.cpp - Library for a momentary button configured as a pullup.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyButton.h>

Button::Button(uint8_t pin) : PinComponent(pin)
{
  _clickCounter = 0;
  _longPressed = false;
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
  _buttonOn = false;
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

boolean Button::popLongPressed()
{
  if (_longPressed)
  {
    _longPressed = false;
    return true;
  }
  return false;
}

bool Button::isOn() { return _buttonOn; }

void Button::setOn(bool buttonOn)
{
  _buttonOn = buttonOn;
}

unsigned long Button::update(unsigned long time)
{
  int value = digitalRead(_pin);

  // this 1000 is the duration within which to pick up click, should be adjustable
  // long pressed logic
  //  if (value == LOW)
  //  {
  //    unsigned long time = millis();
  //    _longPressed = (_pressTime != 0 && (time - _pressTime) >= duration);
  //    return _longPressed;
  //  }
  //  return false;

  if (value == LOW && _pressTime == 0)
  {
    _pressTime = time;
    _releaseTime = 0;
    _prevValue = value;
    DEBUG_DEBUG("button pressed first time %lu", time);
  }
  else if (value == HIGH && _prevValue == LOW)
  {
    _tempClickCounter += 1;
    _releaseTime = time;
    _pressTime = 0;
    _prevValue = value;
    DEBUG_DEBUG("button pressed %i clicks at %lu", _tempClickCounter, time);
  }

  if (_releaseTime != 0)
  {
    // wait for the delay to elapse, before registering the click counter
    if ((time - _releaseTime) >= 200)
    {
      _clickCounter = _tempClickCounter;
      DEBUG_DEBUG("button registered %i clicks at %lu", _clickCounter, time);
    }
  }

  // we always need to check the button status
  return 1;
}