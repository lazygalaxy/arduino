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

const char a1[] PROGMEM = "a1.wav";
const char a2[] PROGMEM = "a2.wav";
const char *const GEN[] PROGMEM = {a1, a2};

const char b1[] PROGMEM = "b1.wav";
const char b2[] PROGMEM = "b2.wav";
const char b3[] PROGMEM = "b3.wav";
const char b4[] PROGMEM = "b4.wav";
const char b5[] PROGMEM = "b5.wav";
const char b6[] PROGMEM = "b6.wav";
const char b7[] PROGMEM = "b7.wav";
const char b8[] PROGMEM = "b8.wav";
const char *const HST[] PROGMEM = {b1, b2, b3, b4, b5, b6, b7, b8};

const char c1[] PROGMEM = "c1.wav";
const char c2[] PROGMEM = "c2.wav";
const char c3[] PROGMEM = "c3.wav";
const char c4[] PROGMEM = "c4.wav";
const char c5[] PROGMEM = "c5.wav";
const char c6[] PROGMEM = "c6.wav";
const char c7[] PROGMEM = "c7.wav";
const char c8[] PROGMEM = "c8.wav";
const char *const SST[] PROGMEM = {c1, c2, c3, c4, c5, c6, c7, c8};

char stringBuffer[7];

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
    strcpy_P(stringBuffer, (char *)pgm_read_word(&(HST[random(8)])));
    wavPlayer.play(stringBuffer);
    neopixel.setNoSequence(0, 0, 255);
    delay(100);
    neopixel.setNoSequence(hue);
  }
  else if (accel >= 200)
  {
    toneSpeaker.stopTone();
    strcpy_P(stringBuffer, (char *)pgm_read_word(&(SST[random(8)])));
    wavPlayer.play(stringBuffer);
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
  // then implement the light saber logic
  if (!lightSaberOn && clicks > 0)
  {
    // turn on the light saber with any button click
    lightSaberOn = true;
    led.stopBlink();
    led.setLight(true);
    strcpy_P(stringBuffer, (char *)pgm_read_word(&(GEN[0])));
    wavPlayer.play(stringBuffer);
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
      strcpy_P(stringBuffer, (char *)pgm_read_word(&(GEN[1])));
      wavPlayer.play(stringBuffer);
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

  led.startBlink();
  button.startClicksCallback(clicksCallback);
}

void loop()
{
  Circuit::loop();
}
