/*
   LazyGalaxyCommon.h - Common stuff for other LazyGalaxy classes
   Created by LazyGalaxy - Evangelos Papakonstantis, February 21, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYCOMMON_H
#define LAZYGALAXYCOMMON_H

#include <Arduino.h>
#include <Arduino_DebugUtils.h>

static const uint8_t D0 = 0;
static const uint8_t D1 = 1;
static const uint8_t D2 = 2;
static const uint8_t D3 = 3;
static const uint8_t D4 = 4;
static const uint8_t D5 = 5;
static const uint8_t D6 = 6;
static const uint8_t D7 = 7;
static const uint8_t D8 = 8;
static const uint8_t D9 = 9;
static const uint8_t D10 = 10;
static const uint8_t D11 = 11;
static const uint8_t D12 = 12;
static const uint8_t D13 = 13;

typedef unsigned long (*updateCallbackPtr)(unsigned long time);
typedef void (*finalCallbackPtr)(unsigned long time);

class Component
{
public:
  unsigned long _triggerTime = 0;
  finalCallbackPtr _finalCallback = nullptr;

  virtual unsigned long update(unsigned long time) { return 0; }
  virtual void setup() {}

  virtual void reset()
  {
    _triggerTime = 0;
    _finalCallback = nullptr;
  }
};

class PinComponent : public Component
{
public:
  explicit PinComponent(uint8_t pin)
  {
    _pin = pin;
  }

  uint8_t getPin() { return _pin; }

  bool isDigital() { return _pin < A0; }

protected:
  uint8_t _pin;
};

#endif