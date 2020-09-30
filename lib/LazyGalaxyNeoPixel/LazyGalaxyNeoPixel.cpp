/*
   LazyGalaxyNeoPixel.cpp - Library for controlling an ws2812 LED strip.
   Created by LazyGalaxy - Evangelos Papakonstantis, November 7, 2018.
   Released into the public domain.
 */

#include <LazyGalaxyNeoPixel.h>

NeoPixel::NeoPixel(char pin, unsigned short pixels) : Component(pin) {
  _strip = new Adafruit_NeoPixel(pixels, pin, NEO_GRB + NEO_KHZ800);
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

void NeoPixel::off() { noSequence(0, 0.0, 0.0); }

void NeoPixel::wipeSequence(float hue, float saturation, float value,
                            unsigned long delayMicros, bool reverse) {
  for (uint16_t i = 0; i < _strip->numPixels(); i++) {
    uint16_t index = i;
    if (reverse) {
      index = _strip->numPixels() - i - 1;
    }
    setHSVColor(index, hue, saturation, value);
    delay(delayMicros);
  }
}

void NeoPixel::chaseSequence(float hue, float saturation, float value,
                             unsigned long delayMicros, unsigned short cycles,
                             unsigned short gap) {
  for (unsigned short c = 0; c < cycles; c++) {
    for (uint16_t i = 0; i < _strip->numPixels(); i++) {
      if ((i + c) % gap == 0) {
        setHSVColor(i, hue, saturation, value, false);
      } else {
        setRGBColor(i, 0, 0, 0);
      }
    }
    _strip->show();
    delay(delayMicros);
  }
}

void NeoPixel::noSequence(float hue, float saturation, float value) {
  for (uint16_t i = 0; i < _strip->numPixels(); i++) {
    setHSVColor(i, hue, saturation, value, false);
  }
  _strip->show();
}
