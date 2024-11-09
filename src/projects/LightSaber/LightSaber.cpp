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
#include <LazyGalaxySDCard.h>
#include <LazyGalaxyToneSpeaker.h>
#include <LazyGalaxyWAVPlayer.h>

// const char *GEN[2] = {"a1", "a2"};
// const char *HST[8] = {"b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8"};
// const char *SST[8] = {"c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8"};

// variables to track the state of the lightsaber
bool lightSaberOn = false;
int8_t hue = 0;
uint16_t freq_prev = 20;

// all lightsaber components
MyButton button(D5);
MyLED led(D4);
MySDCard sdCard(D10);
MyToneSpeaker toneSpeaker(D9, 2);
MyNeoPixel neopixel(D6, 33);
MyMotion motion(D10); // A4 //A5
MyWAVPlayer wavPlayer(D9, 3);

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
    wavPlayer.play("b1.wav");
  }
  else if (accel >= 200)
  {
    toneSpeaker.stopTone();
    wavPlayer.play("c1.wav");
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
  // then implement the light saber logic
  if (!lightSaberOn && clicks > 0)
  {
    // turn on the light saber with any button click
    lightSaberOn = true;
    led.stopBlink();
    led.setLight(true);
    wavPlayer.play("a1.wav");
    neopixel.setWipeSequence(hue);
    motion.startCallback(motionCallback);
    button.startLongPressCallback(longPressCallback, 100, 1000);
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
      wavPlayer.play("a2.wav");
      lightSaberOn = false;
      break;
    }
}

void setup()
{
  // Serial.begin(9600);
  //  System setup
  Circuit::add(&led);
  Circuit::add(&button);
  Circuit::add(&sdCard);
  Circuit::add(&toneSpeaker);
  Circuit::add(&motion);
  Circuit::add(&neopixel);
  Circuit::add(&wavPlayer);
  Circuit::setup();

  if (!Circuit::statusOK)
    Serial.println(F("circuit error"));
  else
    Serial.println(F("circuit ok"));

  led.startBlink();
  button.startClicksCallback(clicksCallback);
}

void loop()
{
  Circuit::loop();
}
