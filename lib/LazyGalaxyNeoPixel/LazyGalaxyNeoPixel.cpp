/*
   LazyGalaxyNeoPixel.cpp - Library for controlling an ws2812 LED strip.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 7, 2018.
   Released into the public domain.
 */

#include <LazyGalaxyNeoPixel.h>

NeoPixel::NeoPixel(char pin, unsigned short pixels) : Component(pin) {
  _strip = new Adafruit_NeoPixel(pixels, pin, NEO_GRB + NEO_KHZ800);
  stopSequence();
}

void NeoPixel::setup() {
  _strip->begin();
  _strip->show();
  off();
}

void NeoPixel::setRGBColor(unsigned short pixel, float red, float green,
                           float blue, bool mustShow) {
  uint8_t convertRed = 255 * red;
  uint8_t convertGre = 255 * green;
  uint8_t convertBlu = 255 * blue;

  _strip->setPixelColor(pixel,
                        _strip->Color(convertRed, convertGre, convertBlu));
  if (mustShow) {
    _strip->show();
  }
}

void NeoPixel::setHSVColor(unsigned short pixel, float hue, float saturation,
                           float value, bool mustShow) {
  uint16_t convertHue = 65535 * hue;
  uint8_t convertSat = 255 * saturation;
  uint8_t convertVal = 255 * value;

  _strip->setPixelColor(pixel, _strip->gamma32(_strip->ColorHSV(
                                   convertHue, convertSat, convertVal)));
  if (mustShow) {
    _strip->show();
  }
}

void NeoPixel::off() { setSimpleSequence(0.0, 0.0, 0.0); }

void NeoPixel::setWipeSequence(float hue, float saturation, float value,
                               unsigned int sequenceDealy, bool reverse,
                               taskCallbackPtr finalCallback) {
  _sequence = WIPE_SEQUENCE;
  _sequenceHue = hue;
  _sequenceSaturation = saturation;
  _sequenceValue = value;
  _sequenceDelay = sequenceDealy;
  _sequenceReverse = reverse;
  _finalCallback = finalCallback;

  _sequenceTaskId = Timer::getInstance()->schedule(update(millis()), this);
}

void NeoPixel::setChaseSequence(float hue, float saturation, float value,
                                unsigned int sequenceDealy,
                                unsigned short cycles, unsigned short gap,
                                taskCallbackPtr finalCallback) {
  _sequence = CHASE_SEQUENCE;
  _sequenceHue = hue;
  _sequenceSaturation = saturation;
  _sequenceValue = value;
  _sequenceDelay = sequenceDealy;

  _finalCallback = finalCallback;

  for (unsigned short c = 0; c < cycles; c++) {
    for (uint16_t i = 0; i < _strip->numPixels(); i++) {
      if ((i + c) % gap == 0) {
        setHSVColor(i, hue, saturation, value, false);
      } else {
        setRGBColor(i, 0, 0, 0);
      }
    }
    _strip->show();
    // TODO: user timer
    // delay(sequenceDealy);
  }
}

void NeoPixel::setSimpleSequence(float hue, float saturation, float value,
                                 float probability) {
  for (uint16_t i = 0; i < _strip->numPixels(); i++) {
    if (probability >= random(1000) / 1000.0f) {
      setHSVColor(i, hue, saturation, value, false);
    } else {
      setHSVColor(i, 0.0, 0.0, 0.0, false);
    }
  }
  _strip->show();
}

void NeoPixel::stopSequence() {
  _sequence = NO_SEQUENCE;
  _sequenceHue = 0.0;
  _sequenceSaturation = 0.0;
  _sequenceValue = 0.0;
  _sequenceDelay = 0;
  _sequenceReverse = false;
  _sequenceCurrentIndex = 0;
  _finalCallback = nullptr;
}

unsigned long NeoPixel::update(unsigned long time) {
  switch (_sequence) {
    case CHASE_SEQUENCE:
      return time + _sequenceDelay;
      break;
    case WIPE_SEQUENCE:
      if (_sequenceCurrentIndex < _strip->numPixels()) {
        uint16_t index = _sequenceCurrentIndex;
        if (_sequenceReverse) {
          index = _strip->numPixels() - _sequenceCurrentIndex - 1;
        }
        setHSVColor(index, _sequenceHue, _sequenceSaturation, _sequenceValue);
        _sequenceCurrentIndex++;
        return time + _sequenceDelay;
      } else {
        taskCallbackPtr tempFinalCallback = _finalCallback;
        stopSequence();
        if (tempFinalCallback != nullptr) {
          tempFinalCallback(time);
        }
      }
      break;
  }

  return time;
}
