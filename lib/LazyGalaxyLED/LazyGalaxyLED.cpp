/*
   LazyGalaxyLED.cpp - Library for controlling a LED
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyLED.h>

LED::LED(uint8_t pin) : PinComponent(pin)
{
}

void LED::setup()
{
  pinMode(_pin, OUTPUT);
}

void LED::reset()
{
  Component::reset();
  _blinkDelay = 0;
  setLight(false);
}

void LED::setLight(bool flag)
{
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

bool LED::isLight()
{
  if (isDigital())
    return digitalRead(_pin) == HIGH;
  else
    return analogRead(_pin) > 0;
}

void LED::startBlink(bool flag, unsigned int blinkDelay)
{
  if (flag && !isActive())
  {
    // we would like to start the blink
    _blinkDelay = blinkDelay;
    _triggerTime = update(millis());
  }
  else if (!flag && isActive())
    reset();
}

unsigned long LED::update(unsigned long time)
{
  setLight(!isLight());
  return time + _blinkDelay;
}
