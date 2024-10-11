/*
   LazyGalaxyNeoPixel.cpp - Library for controlling an ws2812 LED strip.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 7, 2018.
   Released into the public domain.
 */

#include <LazyGalaxyNeoPixel.h>

NeoPixel::NeoPixel(char pin, unsigned short pixels) : PinComponent(pin)
{
  _strip = new Adafruit_NeoPixel(pixels, pin, NEO_GRB + NEO_KHZ800);
  stopSequence();
}

void NeoPixel::setup()
{
  _strip->begin();
  _strip->show();
  off();
}

void NeoPixel::setRGBColor(unsigned short pixel, float red, float green,
                           float blue, bool mustShow)
{
  uint8_t convertRed = 255 * red;
  uint8_t convertGre = 255 * green;
  uint8_t convertBlu = 255 * blue;

  _strip->setPixelColor(pixel,
                        _strip->Color(convertRed, convertGre, convertBlu));
  if (mustShow)
    _strip->show();
}

void NeoPixel::setHSVColor(unsigned short pixel, float hue, float saturation,
                           float value, bool mustShow)
{
  uint16_t convertHue = 65535 * hue;
  uint8_t convertSat = 255 * saturation;
  uint8_t convertVal = 255 * value;

  _strip->setPixelColor(pixel, _strip->gamma32(_strip->ColorHSV(
                                   convertHue, convertSat, convertVal)));
  if (mustShow)
    _strip->show();
}

void NeoPixel::off() { setNoSequence(0.0, 0.0, 0.0); }

void NeoPixel::setWipeSequence(float hue, float saturation, float value,
                               unsigned int delay, bool reverse,
                               finalCallbackPtr finalCallback)
{
  stopSequence();
  _sequenceType = WIPE_SEQUENCE_TYPE;
  _sequenceHue = hue;
  _sequenceSaturation = saturation;
  _sequenceValue = value;
  _sequenceDelay = delay;
  _sequenceReverse = reverse;

  _sequenceTaskId = Timer::getInstance()->schedule(update(millis()), this, finalCallback);
}

void NeoPixel::setChaseSequence(float hue, float saturation, float value,
                                unsigned int delay, unsigned short cycles,
                                unsigned char gap,
                                finalCallbackPtr finalCallback)
{
  stopSequence();
  _sequenceType = CHASE_SEQUENCE_TYPE;
  _sequenceHue = hue;
  _sequenceSaturation = saturation;
  _sequenceValue = value;
  _sequenceDelay = delay;
  _sequenceCycles = cycles;
  _sequenceGap = gap;

  _sequenceTaskId = Timer::getInstance()->schedule(update(millis()), this, finalCallback);
}

void NeoPixel::setNoSequence(float hue, float saturation, float value,
                             float probability)
{
  stopSequence();
  for (uint16_t i = 0; i < _strip->numPixels(); i++)
  {
    if (probability >= random(1000) / 1000.0f)
      setHSVColor(i, hue, saturation, value, false);
    else
      setHSVColor(i, 0.0, 0.0, 0.0, false);
  }
  _strip->show();
}

void NeoPixel::stopSequence()
{
  if (_sequenceTaskId != 0)
    Timer::getInstance()->unschedule(_sequenceTaskId);

  _sequenceTaskId = 0;
  _sequenceType = NO_SEQUENCE_TYPE;
  _sequenceHue = 0.0;
  _sequenceSaturation = 0.0;
  _sequenceValue = 0.0;
  _sequenceDelay = 0;
  _sequenceReverse = false;
  _sequenceCycles = 0;
  _sequenceGap = 0;
  _sequenceIndex = 0;
}

unsigned long NeoPixel::update(unsigned long time)
{
  boolean sequenceComplete = false;
  switch (_sequenceType)
  {
  case CHASE_SEQUENCE_TYPE:
    if (_sequenceIndex < _sequenceCycles)
    {
      for (uint16_t i = 0; i < _strip->numPixels(); i++)
      {
        if ((i + _sequenceIndex) % _sequenceGap == 0)
          setHSVColor(i, _sequenceHue, _sequenceSaturation, _sequenceValue, false);
        else
          setRGBColor(i, 0, 0, 0, false);
      }
      _strip->show();
    }
    else
      sequenceComplete = true;
    break;
  case WIPE_SEQUENCE_TYPE:
    if (_sequenceIndex < _strip->numPixels())
    {
      uint16_t index = _sequenceIndex;
      if (_sequenceReverse)
        index = _strip->numPixels() - _sequenceIndex - 1;
      setHSVColor(index, _sequenceHue, _sequenceSaturation, _sequenceValue);
    }
    else
      sequenceComplete = true;
    break;
  }

  if (sequenceComplete)
  {
    stopSequence();
    return time;
  }
  else
  {
    _sequenceIndex++;
    return time + _sequenceDelay;
  }
}
