/*
   LazyGalaxyLED.cpp - Library for controlling a LED
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyLED.h>

LED::LED(uint8_t pin) : PinComponent(pin)
{
  pinMode(_pin, OUTPUT);
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

void LED::setBlink(bool flag, unsigned int blinkDelay)
{
  if (flag && !isBlink())
  {
    // we would like to start the blink
    _blinkDelay = blinkDelay;
    _triggerTime = update(millis());
  }
  else if (!flag && isBlink())
  {
    // we would like to stop the blink
    _blinkDelay = 0;
    setLight(false);
  }
}

bool LED::isBlink() { return _blinkDelay > 0; }

unsigned long LED::update(unsigned long time)
{
  if (isBlink())
  {
    if (isLight())
      setLight(false);
    else
      setLight(true);
    return time + _blinkDelay;
  }
  return 0;
}
