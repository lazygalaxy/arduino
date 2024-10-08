/*
   LazyGalaxyButton.cpp - Library for a momentary button configured as a pullup.
   Created by LazyGalaxy - Evangelos Papakonstantis, October 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyButton.h>

Button::Button(uint8_t buttonPin, uint8_t ledPin) : PinComponent(buttonPin)
{
  pinMode(buttonPin, INPUT_PULLUP);
  if (ledPin >= 0)
  {
    led = new LED(ledPin);
  }
}

int Button::getClicks(unsigned int delay)
{
  unsigned long time = millis();
  int value = digitalRead(_pin);

  if (value == LOW && _pressTime == 0)
  {
    _pressTime = time;
    _releaseTime = 0;
  }
  else if (value == HIGH && _prevValue == LOW)
  {
    _clickCounter += 1;
    _releaseTime = time;
    _pressTime = 0;
  }

  if (_releaseTime != 0 && (time - _releaseTime) >= delay)
  {
    int clickCounter = _clickCounter;

    if (_longPressed)
    {
      clickCounter = 0;
    }

    _releaseTime = 0;
    _pressTime = 0;
    _prevValue = HIGH;
    _clickCounter = 0;
    _longPressed = false;

    debugPrintln("getClicks returns " + String(clickCounter));

    return clickCounter;
  }

  _prevValue = value;
  return 0;
}

boolean Button::isLongPressed(unsigned int duration)
{
  int value = digitalRead(_pin);
  if (value == LOW)
  {
    unsigned long time = millis();
    _longPressed = (_pressTime != 0 && (time - _pressTime) >= duration);
    return _longPressed;
  }
  return false;
}

bool Button::isOn() { return _buttonOn; }

bool Button::isOff() { return !_buttonOn; }

void Button::setOn(bool buttonOn)
{
  _buttonOn = buttonOn;
  if (led != nullptr && buttonOn)
  {
    led->setLight(true);
  }
  else if (led != nullptr && !buttonOn)
  {
    led->setLight(false);
  }
}