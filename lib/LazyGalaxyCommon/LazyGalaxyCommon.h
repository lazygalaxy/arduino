/*
   LazyGalaxyCommon.h - Common stuff for other LazyGalaxy classes
   Created by LazyGalaxy - Evangelos Papakonstantis, February 21, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYCOMMON_H
#define LAZYGALAXYCOMMON_H

#include <Arduino.h>

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

static void debugPrintln(boolean isDebug, int buffSize, const char *message, va_list args)
{
  if (isDebug)
  {
    char buff[buffSize];
    sprintf(buff, message, args);
    Serial.println(buff);
  }
}

static void debugPrintln(boolean isDebug, int buffSize, const char *message, int argSize, ...)
{
  if (isDebug)
  {
    va_list args;
    va_start(args, argSize);
    debugPrintln(isDebug, buffSize, message, args);
  }
}

static void debugPrintln(int buffSize, const char *message, int argSize, ...)
{
  va_list args;
  va_start(args, argSize);
  debugPrintln(true, buffSize, message, args);
}

static void debugPrintln(boolean isDebug, const char *message)
{
  if (isDebug)
    Serial.println(message);
}

static void debugPrintln(const char *message)
{
  debugPrintln(true, message);
}

class Component
{
public:
  virtual unsigned long update(unsigned long time) { return time; }
  virtual void setup() {}
};

class PinComponent : public Component
{
public:
  explicit PinComponent(uint8_t pin)
  {
    _pin = pin;
    _debug = false;
  }

  uint8_t getPin() { return _pin; }

  bool isDigital() { return _pin < A0; }

  void enableDebug()
  {
    _debug = true;
  }

protected:
  bool _debug;
  uint8_t _pin;
};

#endif