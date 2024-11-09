/*
   LightSaber.cpp - LightSaber implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyButton.h>
#include <LazyGalaxyCircuit.h>
#include <LazyGalaxyLED.h>
//  #include <LazyGalaxyMotion.h>
#include <LazyGalaxyNeoPixel.h>
// #include <LazyGalaxySDCard.h>
//   #include <LazyGalaxyToneSpeaker.h>
// #include <LazyGalaxyWAVPlayer.h>

// variables to track the state of the lightsaber
bool lightSaberOn = false;
int8_t hue = 0;
// int freq_prev = 20;
// uint32_t lastHardHitTime = 0;
// uint32_t lastSoftHitTime = 0;
// uint32_t lastHardSwingTime = 0;
// uint32_t lastSoftSwingTime = 0;

// all lightsaber components
Button *button = new Button(D5);
MyLED *led = new MyLED(D4);
// MySDCard *sdCard = new MySDCard(D10);
// MyToneSpeaker *toneSpeaker = new MyToneSpeaker(D9, SPEAKER_VOLUME);
NeoPixel *neopixel = new NeoPixel(D6, 33);
// MyMotion *motion = new MyMotion(D10); // A4 //A5
// MyWAVPlayer *wavPlayer = new MyWAVPlayer(D9, 2);

// void motionCallback(unsigned long time, unsigned long accel, unsigned long gyro)
// {
//   // unsigned long COMPL = accel + gyro;
//   // int freq = (long)COMPL * COMPL / 1500; // parabolic tone change
//   // freq = constrain(freq, 18, 300);
//   // int freq_new = freq * FREQ_SMOOTH_FACTOR + freq_prev * (1 - FREQ_SMOOTH_FACTOR); // smooth filter
//   //  if (freq_new != freq_prev)
//   //    toneSpeaker->playTone(freq_new);

//   if (accel >= 320)
//   {
//     if (time - lastHardHitTime > 1000)
//     {
//       // Serial.print("hard hit ");
//       // Serial.println(time);
//       lastHardHitTime = time;
//       wavPlayer->play("hst1.wav");
//     }
//   }
//   else if (accel >= 150)
//   {
//     if (time - lastSoftHitTime > 1000 && time - lastHardHitTime > 1000)
//     {
//       // Serial.print("soft hit ");
//       // Serial.println(time);
//       lastSoftHitTime = time;
//       wavPlayer->play("sst1.wav");
//     }
//   }
//   else if (gyro >= 300)
//   {
//     if (time - lastHardSwingTime > 1000 && time - lastSoftHitTime > 1000 && time - lastHardHitTime > 1000)
//     {
//       // Serial.print("hard swing ");
//       // Serial.println(time);
//       lastHardSwingTime = time;
//       wavPlayer->play("hsw1.wav");
//     }
//   }
//   else if (gyro >= 150)
//   {
//     if (time - lastSoftSwingTime > 1000 && time - lastHardSwingTime > 1000 && time - lastSoftHitTime > 1000 && time - lastHardHitTime > 1000)
//     {
//       // Serial.print("soft swing ");
//       // Serial.println(time);
//       lastSoftSwingTime = time;
//       wavPlayer->play("ssw1.wav");
//     }
//   }

//   // freq_prev = freq_new;
// }

void longPressCallback(unsigned long time)
{
  hue += 5;
  if (hue > 255)
    hue = 0;
  neopixel->setNoSequence(hue);
}

void clicksCallback(unsigned long time, uint8_t clicks)
{
  // then implement the light saber logic
  if (!lightSaberOn && clicks > 0)
  {
    // turn on the light saber with any button click
    lightSaberOn = true;
    led->stopBlink();
    led->setLight(true);
    // wavPlayer->play("on.wav");
    neopixel->setWipeSequence(hue);
    //  motion->startCallback(motionCallback);
    //  toneSpeaker->playTone(freq_prev);
    button->startLongPressCallback(longPressCallback, 100, 1000);
  }
  else if (lightSaberOn)
    switch (clicks)
    {
    case 1:
      // if there is 1 click, stop the light saber
      button->stopLongPressCallback();
      // toneSpeaker->stopTone();
      // motion->stopCallback();
      neopixel->setWipeSequence(0, 0, 0, true);
      led->startBlink();
      // wavPlayer->play("off.wav");
      lightSaberOn = false;
      break;
    }
}

void setup()
{
  // Serial.begin(115200);
  // System setup
  Circuit::add(led);
  Circuit::add(button);
  // Circuit::add(sdCard);
  // Circuit::add(toneSpeaker);
  // Circuit::add(motion);
  Circuit::add(neopixel);
  // Circuit::add(wavPlayer);
  Circuit::setup();

  // if (!Circuit::statusOK)
  //   Serial.println(F("circuit error"));
  // else
  //   Serial.println(F("circuit ok"));

  led->startBlink();
  button->startClicksCallback(clicksCallback);
  // wavPlayer->play("hum.wav");
}

void loop()
{
  Circuit::loop();
}
