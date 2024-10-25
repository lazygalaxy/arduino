/*
   LightSaber.cpp - LightSaber implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyButton.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyNeoPixel.h>
#include <LazyGalaxyMotion.h>
#include <LazyGalaxyAudioPlayer.h>
#include <LazyGalaxyToneSpeaker.h>

// fixed values
// the delay with which each succesive LED light is turned on and off
static const unsigned int NEOPIXEL_DELAY_MILLIS = 10;
// the saturation of all LED lights
static const float NEOPIXEL_SAT = 1.0;
// the value of all LED lights
static const float NEOPIXEL_VAL = 0.5;
// the smooth factor used on the freq of tones played
static const float FREQ_SMOOTH_FACTOR = 0.2;
// the speaker volume from 0..10
static const uint8_t SPEAKER_VOLUME = 10;

// variables to track the state of the lightsaber
bool lightSaberOn = false;
float hue = 0.0;
int freq_prev = 20;

// all lightsaber components
Button *button = new Button(D5);
LED *led = new LED(D4);
MyToneSpeaker *toneSpeaker = new MyToneSpeaker(D9, SPEAKER_VOLUME);
MyAudioPlayer *audioPlayer = new MyAudioPlayer(D10, D11, SPEAKER_VOLUME * 3);
NeoPixel *neopixel = new NeoPixel(D6, 33);
MyMotion *motion = new MyMotion(10); // A4 //A5

void motionCallback(unsigned long time, unsigned long accel, unsigned long gyro)
{
  unsigned long COMPL = accel + gyro;
  int freq = (long)COMPL * COMPL / 1500; // parabolic tone change
  freq = constrain(freq, 18, 300);
  int freq_new = freq * FREQ_SMOOTH_FACTOR + freq_prev * (1 - FREQ_SMOOTH_FACTOR); // smooth filter
  if (freq_new != freq_prev)
    toneSpeaker->playTone(freq_new);
  if (accel >= 320)
    audioPlayer->play(2, 1);
  else if (accel >= 150)
    audioPlayer->play(3, 1);
  //  else if (gyro >= 300)
  //    DEBUG_VERBOSE("hard swing at %lu with %i", time, gyro);
  //  else if (gyro >= 150)
  //    DEBUG_VERBOSE("soft swing at %lu with %i", time, gyro);
  freq_prev = freq_new;
}

void longPressCallback(unsigned long time)
{
  hue += 0.01;
  if (hue > 1.0)
    hue = 0.0;
  neopixel->setNoSequence(hue, NEOPIXEL_SAT, NEOPIXEL_VAL);
}

void clicksCallback(unsigned long time, int clicks)
{
  // then implement the light saber logic
  if (!lightSaberOn && clicks > 0)
  {
    // turn on the light saber with any button click
    lightSaberOn = true;
    led->stopBlink();
    led->setLight(true);
    audioPlayer->play(1, 1);
    neopixel->setWipeSequence(hue, NEOPIXEL_SAT, NEOPIXEL_VAL, NEOPIXEL_DELAY_MILLIS, false);
    motion->startCallback(motionCallback);
    toneSpeaker->playTone(freq_prev);
    button->startLongPressCallback(longPressCallback);
  }
  else if (lightSaberOn)
    switch (clicks)
    {
    case 1:
      // if there is 1 click, stop the light saber
      button->stopLongPressCallback();
      toneSpeaker->stopTone();
      motion->stopCallback();
      neopixel->setWipeSequence(0.0, 0.0, 0.0, NEOPIXEL_DELAY_MILLIS, true);
      led->startBlink();
      audioPlayer->play(1, 2);
      lightSaberOn = false;
      break;
    }
}

void setup()
{
  // System setup
  Circuit::add(led);
  Circuit::add(button);
  Circuit::add(toneSpeaker);
  Circuit::add(audioPlayer);
  Circuit::add(motion);
  Circuit::add(neopixel);
  Circuit::setup();

  led->startBlink();
  button->startClicksCallback(clicksCallback);
  audioPlayer->play(1, 3);
}

void loop()
{
  Circuit::loop();
}
