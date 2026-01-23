/*
   LightSaber.cpp - LightSaber implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyButton.h>
#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyMotion.h>
#include <LazyGalaxyNeoPixel.h>
#include <LazyGalaxyToneSpeaker.h>
#include <LazyGalaxyWAVPlayer.h>

const char on[] = "/a1.wav";
const char off[] = "/a2.wav";

const char b1[] = "/b1.wav";
const char b2[] = "/b2.wav";
const char b3[] = "/b3.wav";
const char b4[] = "/b4.wav";
const char b5[] = "/b5.wav";
const char b6[] = "/b6.wav";
const char b7[] = "/b7.wav";
const char b8[] = "/b8.wav";
const char *const hard_strike[] = {b1, b2, b3, b4, b5, b6, b7, b8};

const char c1[] = "/c1.wav";
const char c2[] = "/c2.wav";
const char c3[] = "/c3.wav";
const char c4[] = "/c4.wav";
const char c5[] = "/c5.wav";
const char c6[] = "/c6.wav";
const char c7[] = "/c7.wav";
const char c8[] = "/c8.wav";
const char *const soft_strike[] = {c1, c2, c3, c4, c5, c6, c7, c8};

// variables to track the state of the lightsaber
bool lightSaberOn = false;
int8_t hue = 0;
uint16_t freq_prev = 20;
uint8_t volume = 40;

// all lightsaber components
MyButton button(19);
MyLED led(18);
MyToneSpeaker toneSpeaker(4, volume);
MyNeoPixel neopixel(12, 33);
MyMotion motion;
MyWAVPlayer wavPlayer(volume);

void motionCallback(unsigned long time, uint16_t accel, uint16_t gyro)
{
  uint32_t sum = accel + gyro;
  uint16_t freq = (sum * sum) / 1500;
  freq = constrain(freq, 18, 300);
  uint16_t freq_new = (freq * 0.2) + (freq_prev * 0.8);

  if (!wavPlayer.isPlaying())
    toneSpeaker.playTone(freq_new);

  if (accel >= 320)
  {
    toneSpeaker.stopTone();
    wavPlayer.play(hard_strike[random(8)]);
    neopixel.setNoSequence(0, 0, 255);
    delay(100);
    neopixel.setNoSequence(hue);
  }
  else if (accel >= 200)
  {
    toneSpeaker.stopTone();
    wavPlayer.play(soft_strike[random(8)]);
    neopixel.setNoSequence(0, 0, 255);
    delay(50);
    neopixel.setNoSequence(hue);
  }
  // else if (gyro >= 300)
  // {
  //   if (time - lastHardSwingTime > 1000 && time - lastSoftHitTime > 1000 && time - lastHardHitTime > 1000)
  //   {
  //     // Serial.print("hard swing ");
  //     // Serial.println(time);
  //     lastHardSwingTime = time;
  //     wavPlayer->play("hsw1.wav");
  //   }
  // }
  // else if (gyro >= 150)
  // {
  //   if (time - lastSoftSwingTime > 1000 && time - lastHardSwingTime > 1000 && time - lastSoftHitTime > 1000 && time - lastHardHitTime > 1000)
  //   {
  //     // Serial.print("soft swing ");
  //     // Serial.println(time);
  //     lastSoftSwingTime = time;
  //     wavPlayer->play("ssw1.wav");
  //   }
  // }

  freq_prev = freq_new;
}

void longPressCallback(unsigned long time)
{
  hue += 5;
  if (hue > 255)
    hue = 0;
  neopixel.setNoSequence(hue);
}

void clicksCallback(unsigned long time, uint8_t clicks)
{
  Serial.println("clickscallback");
  // then implement the light saber logic
  if (!lightSaberOn && clicks > 0)
  {
    Serial.println("button clicked");
    // turn on the light saber with any button click
    lightSaberOn = true;
    led.stopBlink();
    led.setLight(true);
    wavPlayer.play(on);
    neopixel.setWipeSequence(hue);

    button.startLongPressCallback(longPressCallback, 100, 1000);
    motion.startCallback(motionCallback);
  }
  else if (lightSaberOn)
    switch (clicks)
    {
    case 1:
      // if there is 1 click, stop the light saber
      button.stopLongPressCallback();
      toneSpeaker.stopTone();
      motion.stopCallback();
      neopixel.setWipeSequence(0, 0, 0, true);
      led.startBlink();
      wavPlayer.play(off);
      lightSaberOn = false;
      break;
    }
}

void setup()
{
  Serial.begin(115200);
  //  System setup
  Circuit::add(&led);
  Circuit::add(&button);
  Circuit::add(&toneSpeaker);
  Circuit::add(&motion);
  Circuit::add(&neopixel);
  Circuit::add(&wavPlayer);
  Circuit::setup();

  led.startBlink();
  button.startClicksCallback(clicksCallback);
}

void loop()
{
  Circuit::loop();
}
