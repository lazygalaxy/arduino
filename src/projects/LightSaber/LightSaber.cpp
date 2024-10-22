/*
   LightSaber.cpp - LightSaber implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxySystem.h>
#include <LazyGalaxyButton.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyNeoPixel.h>
#include <LazyGalaxyMotion.h>
// #include <LazyGalaxySDCard.h>
#include <LazyGalaxySpeaker.h>

// fixed values
// the delay with which each succesive LED light is turned on and off
static const unsigned int NEOPIXEL_DELAY_MILLIS = 10;
// the saturation of all LED lights
static const float NEOPIXEL_SAT = 1.0;
// the value of all LED lights
static const float NEOPIXEL_VAL = 0.5;
// the smooth factor used on the freq of tones played
static const float FREQ_SMOOTH_FACTOR = 0.2;

// modifiable vlaues
bool lightSaberOn = false;
float hue = 0.0;
int freq_prev = 20;

LED *led = new LED(D4);
MySpeaker *speaker = new MySpeaker(D9, 10);
NeoPixel *neopixel = new NeoPixel(D6, 33);

void motionCallback(unsigned long time, unsigned long accel, unsigned long gyro)
{
  if (lightSaberOn)
  {
    unsigned long COMPL = accel + gyro;
    int freq = (long)COMPL * COMPL / 1500; // parabolic tone change
    freq = constrain(freq, 18, 300);
    int freq_new = freq * FREQ_SMOOTH_FACTOR + freq_prev * (1 - FREQ_SMOOTH_FACTOR); // smooth filter
    if (freq_new != freq_prev)
      speaker->playNote(freq_new);
    if (accel >= 320)
      DEBUG_DEBUG("hard hit at %lu with %i", time, accel);
    else if (accel >= 150)
      DEBUG_DEBUG("soft hit at %lu with %i", time, accel);
    if (gyro >= 300)
      DEBUG_DEBUG("hard swing at %lu with %i", time, gyro);
    else if (gyro >= 150)
      DEBUG_DEBUG("soft swing at %lu with %i", time, gyro);
    freq_prev = freq_new;
  }
}
MyMotion *motion = new MyMotion(10, motionCallback);

void clicksCallback(unsigned long time, int clicks)
{
  // then implement the light saber logic
  if (!lightSaberOn && clicks > 0)
  {
    // turn on the light saber with any button click
    lightSaberOn = true;
    // speaker->playWav("ON.wav");
    led->setLight(true);
    neopixel->setWipeSequence(hue, NEOPIXEL_SAT, NEOPIXEL_VAL, NEOPIXEL_DELAY_MILLIS, false);
    speaker->playNote(freq_prev);
  }
  else if (lightSaberOn)
  {
    switch (clicks)
    {
    case 1:
      // if there is 1 click, stop the light saber
      // speaker->playWav("OFF.wav");
      neopixel->setWipeSequence(0.0, 0.0, 0.0, NEOPIXEL_DELAY_MILLIS, true);
      led->startBlink(true);
      speaker->reset();
      lightSaberOn = false;
      break;
    }
  }
}

void longPressCallback(unsigned long time)
{
  if (lightSaberOn)
  {
    hue += 0.01;
    if (hue > 1.0)
      hue = 0.0;
    neopixel->setNoSequence(hue, NEOPIXEL_SAT, NEOPIXEL_VAL);
  }
}
Button *button = new Button(D5, clicksCallback, longPressCallback);

void setup()
{
  Serial.begin(9600);
  Debug.setDebugLevel(DBG_DEBUG);

  // System::add(new MySDCard(D10));
  System::add(led);
  System::add(button);
  System::add(speaker);
  System::add(motion);
  System::add(neopixel);

  System::setup();

  led->startBlink(true);
}

void loop()
{
  System::loop();
}
