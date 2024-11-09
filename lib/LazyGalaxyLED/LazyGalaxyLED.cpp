/*
   LazyGalaxyLED.cpp - Library for controlling a LED
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyLED.h>

MyLED::MyLED(uint8_t pin) : PinComponent(pin)
{
}

void MyLED::setup()
{
  pinMode(_pin, OUTPUT);
  setLight(false);
}

void MyLED::reset()
{
  Component::reset();
  _blinkDelay = 0;
}

void MyLED::setLight(bool flag, bool considerDeActivation)
{
  if (considerDeActivation && isActive())
    reset();
  if (flag)
  {
    if (isDigital())
      digitalWrite(_pin, HIGH);
    else
      analogWrite(_pin, 255);
  }
  else
  {
    if (isDigital())
      digitalWrite(_pin, LOW);
    else
      analogWrite(_pin, 0);
  };
}

bool MyLED::isLight()
{
  if (isDigital())
    return digitalRead(_pin) == HIGH;
  else
    return analogRead(_pin) > 0;
}

void MyLED::startBlink(uint16_t blinkDelay)
{
  if (!isActive())
  {
    // we would like to start the blink
    _blinkDelay = blinkDelay;
    _triggerTime = update(millis());
  }
}

void MyLED::stopBlink()
{
  if (isActive())
    reset();
}

unsigned long MyLED::update(unsigned long time)
{
  setLight(!isLight(), false);
  return time + _blinkDelay;
}
