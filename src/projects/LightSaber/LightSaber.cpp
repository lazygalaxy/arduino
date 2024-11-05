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
#include <LazyGalaxySDCard.h>
#include <LazyGalaxyToneSpeaker.h>
#include <LazyGalaxyWAVPlayer.h>

// neopixel fixed values
// the delay with which each succesive LED light is turned on and off
static const unsigned int NEOPIXEL_DELAY_MILLIS = 20;
// the saturation of all LED lights
static const float NEOPIXEL_SAT = 1.0;
// the value of all LED lights
static const float NEOPIXEL_VAL = 0.5;

// sound fixed values
// the speaker volume from 0..10
static const uint8_t SPEAKER_VOLUME = 5;
static const unsigned long PLAY_MIN_TIME = 1000;
// labeled folders
static const uint8_t GENERAL_FOLDER = 1;
static const uint8_t HARDHIT_FOLDER = 2;
static const uint8_t SOFTHIT_FOLDER = 3;
static const uint8_t HARDSWING_FOLDER = 4;
static const uint8_t SOFTSWING_FOLDER = 5;

// the smooth factor used on the freq of tones played
static const float FREQ_SMOOTH_FACTOR = 0.2;

// variables to track the state of the lightsaber
bool lightSaberOn = false;
float hue = 0.0;
// int freq_prev = 20;
unsigned long lastHardHitTime = 0;
unsigned long lastSoftHitTime = 0;
unsigned long lastHardSwingTime = 0;
unsigned long lastSoftSwingTime = 0;

// all lightsaber components
Button *button = new Button(D5);
LED *led = new LED(D4);
MySDCard *sdCard = new MySDCard(D10);
// MyToneSpeaker *toneSpeaker = new MyToneSpeaker(D9, 10);
NeoPixel *neopixel = new NeoPixel(D6, 33);
MyMotion *motion = new MyMotion(10); // A4 //A5
MyWAVPlayer *wavPlayer = new MyWAVPlayer(D9, SPEAKER_VOLUME * 3);

void motionCallback(unsigned long time, unsigned long accel, unsigned long gyro)
{
  // unsigned long COMPL = accel + gyro;
  // int freq = (long)COMPL * COMPL / 1500; // parabolic tone change
  // freq = constrain(freq, 18, 300);
  // int freq_new = freq * FREQ_SMOOTH_FACTOR + freq_prev * (1 - FREQ_SMOOTH_FACTOR); // smooth filter
  //  if (freq_new != freq_prev)
  //    toneSpeaker->playTone(freq_new);

  if (accel >= 320)
  {
    if (time - lastHardHitTime > PLAY_MIN_TIME)
    {
      Serial.print("hard hit ");
      Serial.println(time);
      lastHardHitTime = time;
      // audioPlayer->playRandom(HARDHIT_FOLDER);
    }
  }
  else if (accel >= 150)
  {
    if (time - lastSoftHitTime > PLAY_MIN_TIME && time - lastHardHitTime > PLAY_MIN_TIME)
    {
      Serial.print("soft hit ");
      Serial.println(time);
      lastSoftHitTime = time;
      // audioPlayer->playRandom(SOFTHIT_FOLDER);
    }
  }
  else if (gyro >= 300)
  {
    if (time - lastHardSwingTime > PLAY_MIN_TIME && time - lastSoftHitTime > PLAY_MIN_TIME && time - lastHardHitTime > PLAY_MIN_TIME)
    {
      Serial.print("hard swing ");
      Serial.println(time);
      lastHardSwingTime = time;
      // audioPlayer->playRandom(HARDSWING_FOLDER);
    }
  }
  else if (gyro >= 150)
  {
    if (time - lastSoftSwingTime > PLAY_MIN_TIME && time - lastHardSwingTime > PLAY_MIN_TIME && time - lastSoftHitTime > PLAY_MIN_TIME && time - lastHardHitTime > PLAY_MIN_TIME)
    {
      Serial.print("soft swing ");
      Serial.println(time);
      lastSoftSwingTime = time;
      // audioPlayer->playRandom(SOFTSWING_FOLDER);
    }
  }

  // freq_prev = freq_new;
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
    // audioPlayer->play(GENERAL_FOLDER, 1);
    neopixel->setWipeSequence(hue, NEOPIXEL_SAT, NEOPIXEL_VAL, NEOPIXEL_DELAY_MILLIS, false);
    motion->startCallback(motionCallback);
    // toneSpeaker->playTone(freq_prev);
    button->startLongPressCallback(longPressCallback, 100, 1000);
  }
  else if (lightSaberOn)
    switch (clicks)
    {
    case 1:
      // if there is 1 click, stop the light saber
      button->stopLongPressCallback();
      // toneSpeaker->stopTone();
      motion->stopCallback();
      neopixel->setWipeSequence(0.0, 0.0, 0.0, NEOPIXEL_DELAY_MILLIS, true);
      led->startBlink();
      // audioPlayer->play(GENERAL_FOLDER, 2);
      lightSaberOn = false;
      break;
    }
}

void setup()
{
  // System setup
  Circuit::add(led);
  Circuit::add(button);
  Circuit::add(sdCard);
  // Circuit::add(toneSpeaker);
  Circuit::add(motion);
  Circuit::add(neopixel);
  Circuit::add(wavPlayer);
  Circuit::setup();

  led->startBlink();
  button->startClicksCallback(clicksCallback);
  wavPlayer->play("hum.wav");
}

void loop()
{
  Circuit::loop();
}
