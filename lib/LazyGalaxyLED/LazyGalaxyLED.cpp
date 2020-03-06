/*
   LazyGalaxyLED.cpp - Library for controlling an LED
   Created by LazyGalaxy - Evangelos Papakonstantis, January 29, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyLED.h>

LazyGalaxyLED::LazyGalaxyLED(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

bool LazyGalaxyLED::isDigital() { return _pin < 14; }

void LazyGalaxyLED::setLight(bool flag) {
  if (flag) {
    if (isDigital()) {
      digitalWrite(_pin, HIGH);
    } else {
      analogWrite(_pin, 255);
    }
  } else {
    if (isDigital()) {
      digitalWrite(_pin, LOW);
    } else {
      analogWrite(_pin, 0);
    }
  };
}

bool LazyGalaxyLED::isLight() {
  if (isDigital()) {
    return digitalRead(_pin) == HIGH;
  } else {
    return analogRead(_pin) > 0;
  }
}

void LazyGalaxyLED::setBlink(bool flag, unsigned int blinkDelay) {
  if (flag && !isBlink()) {
    // we would like to start the blink
    _blinkDelay = blinkDelay;
    _blinkTaskId =
        LazyGalaxyTimer::getInstance()->schedule(blinkDelay + millis(), this);
  } else if (!flag && isBlink()) {
    // we would like to stop the blink
    LazyGalaxyTimer::getInstance()->unschedule(_blinkTaskId);
    _blinkDelay = 0;
    _blinkTaskId = 0;
    setLight(false);
  }
}

bool LazyGalaxyLED::isBlink() { return _blinkDelay > 0 && _blinkTaskId > 0; }

unsigned int LazyGalaxyLED::update(unsigned long time) {
  if (isBlink()) {
    if (isLight()) {
      setLight(false);
    } else {
      setLight(true);
    }
    return _blinkDelay;
  }
  return 0;
}
