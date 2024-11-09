/*
   LazyGalaxyNeoPixel.cpp - Library for controlling an ws2812 LED strip.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 7, 2018.
   Released into the public domain.
 */

#include <LazyGalaxyNeoPixel.h>

MyNeoPixel::MyNeoPixel(char pin, uint8_t ledArraySize) : PinComponent(pin)
{
  _ledArraySize = ledArraySize;
}

void MyNeoPixel::setup()
{
  _ledArray = new CRGB[_ledArraySize];
  FastLED.addLeds<WS2812, 6, GRB>(_ledArray, _ledArraySize);
  FastLED.setBrightness(100);
  off();
}

void MyNeoPixel::reset()
{
  Component::reset();
  _sequenceType = NO_SEQUENCE_TYPE;
  _seqHue = 0;
  _seqSat = 0;
  _seqVal = 0;
  _sequenceDelay = 0;
  _sequenceReverse = false;
  //_sequenceCycles = 0;
  //_sequenceGap = 0;
  _sequenceIndex = 0;
}

// void NeoPixel::setRGBColor(int ledIndex, uint8_t red, uint8_t gre, uint8_t blu, bool mustShow)
// {
//   leds[ledIndex] = CRGB(red, gre, blu);
//   if (mustShow)
//     FastLED.show();
// }

void MyNeoPixel::setHSVColor(uint8_t ledIndex, uint8_t hue, uint8_t sat, uint8_t val, bool mustShow)
{
  _ledArray[ledIndex] = CHSV(hue, sat, val);
  if (mustShow)
    FastLED.show();
}

void MyNeoPixel::off()
{
  setNoSequence(0, 0, 0);
}

void MyNeoPixel::setWipeSequence(uint8_t hue, uint8_t sat, uint8_t val, bool reverse, uint16_t delay, finalCallbackPtr finalCallback)
{
  reset();
  _sequenceType = WIPE_SEQUENCE_TYPE;
  _seqHue = hue;
  _seqSat = sat;
  _seqVal = val;
  _sequenceReverse = reverse;
  _sequenceDelay = delay;

  _triggerTime = update(millis());
  _finalCallback = finalCallback;
}

// void NeoPixel::setChaseSequence(uint8_t hue, uint8_t sat, uint8_t val, uint16_t delay, uint8_t cycles, uint8_t gap, finalCallbackPtr finalCallback)
// {
//   reset();
//   _sequenceType = CHASE_SEQUENCE_TYPE;
//   _seqHue = hue;
//   _seqSat = sat;
//   _seqVal = val;
//   _sequenceDelay = delay;
//   _sequenceCycles = cycles;
//   _sequenceGap = gap;

//   _triggerTime = update(millis());
//   _finalCallback = finalCallback;
// }

void MyNeoPixel::setNoSequence(uint8_t hue, uint8_t sat, uint8_t val, uint8_t probability)
{
  reset();
  for (uint8_t i = 0; i < _ledArraySize; i++)
    if (probability >= random(100) + 1)
      setHSVColor(i, hue, sat, val, false);
    else
      setHSVColor(i, 0.0, 0.0, 0.0, false);
  FastLED.show();
}

unsigned long MyNeoPixel::update(unsigned long time)
{
  switch (_sequenceType)
  {
  // case CHASE_SEQUENCE_TYPE:
  //   if (_sequenceIndex < _sequenceCycles)
  //   {
  //     for (uint8_t i = 0; i < _pixels; i++)
  //     {
  //       if ((i + _sequenceIndex) % _sequenceGap == 0)
  //         setHSVColor(i, _seqHue, _seqSat, _seqVal, false);
  //       else
  //         setHSVColor(i, 0, 0, 0, false);
  //     }
  //     FastLED.show();
  //   }
  //   else
  //     return 0;
  case WIPE_SEQUENCE_TYPE:
    if (_sequenceIndex < _ledArraySize)
    {
      int index = _sequenceIndex;
      if (_sequenceReverse)
        index = _ledArraySize - _sequenceIndex - 1;
      setHSVColor(index, _seqHue, _seqSat, _seqVal);
    }
    else
      return 0;
  }

  _sequenceIndex++;
  return time + _sequenceDelay;
}
