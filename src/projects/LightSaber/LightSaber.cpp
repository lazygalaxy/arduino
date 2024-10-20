/*
   LightSaber.cpp - LightSaber implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxySystem.h>
#include <LazyGalaxyButton.h>
#include <LazyGalaxyLED.h>
#include <LazyGalaxyNeoPixel.h>
#include <LazyGalaxySDCard.h>
#include <LazyGalaxySpeaker.h>

// fixed values
// the delay with which each succesive LED light is turned on and off
static const unsigned int NEOPIXEL_DELAY_MILLIS = 20;
// the saturation of all LED lights
static const float NEOPIXEL_SAT = 1.0;
// the value of all LED lights
static const float NEOPIXEL_VAL = 0.5;
// the smooth factor used on the freq of tones played
static const float FREQ_SMOOTH_FACTOR = 0.2;

// modifiable vlaues
// the hue of all LED lights, this is what actually give the colour to the LED lights
float hue = 0.0;

// components required
LED *led = new LED(D4);
Button *button = new Button(D5);
MySpeaker *speaker = new MySpeaker(D9, 5);
NeoPixel *neopixel = new NeoPixel(D6, 33);

void motionCallback(unsigned long time, unsigned long accel, unsigned long gyro)
{
  unsigned long COMPL = accel + gyro;
  int freq = (long)COMPL * COMPL / 1500; // parabolic tone change
  freq = constrain(freq, 18, 300);
  int freq_f = freq * FREQ_SMOOTH_FACTOR + freq_f * (1 - FREQ_SMOOTH_FACTOR); // smooth filter
  speaker->playNote(freq_f);
}

// unsigned long changeHueCallback(unsigned long time)
// {
//   if (button->isLongPressed())
//   {
//     hue += 0.01;
//     if (hue > 1.0)
//       hue = 0.0;
//     neopixel->setNoSequence(hue, NEOPIXEL_SAT, NEOPIXEL_VAL);
//     return time + 100;
//   }
//   return 0;
// }

void setup()
{
  Serial.begin(9600);
  Debug.setDebugLevel(DBG_VERBOSE);

  System::add(new MySDCard(D10));
  System::add(led);
  System::add(button);
  System::add(speaker);
  System::add(neopixel);
  System::setup();

  led->setBlink(true);
}

void loop()
{
  System::loop();

  int buttonClickCounter = button->popClickCounter();
  boolean buttonLongPressed = button->popLongPressed();

  // then implement the light saber logic
  if (!button->isOn() && buttonClickCounter > 0)
  {
    // turn on the light saber with any button click
    led->setLight(true);
    button->setOn(true);
    neopixel->setWipeSequence(hue, NEOPIXEL_SAT, NEOPIXEL_VAL, NEOPIXEL_DELAY_MILLIS, false);
    speaker->playWav("ON.wav");
  }
  else if (button->isOn())
  {
    if (buttonLongPressed)
    {
      // if there is a long press cycle the hue color
      // Timer::scheduleTask(100, changeHueCallback);
    }
    else if (buttonClickCounter == 1)
    {
      // if there is 1 click, stop the light saber
      neopixel->setWipeSequence(0.0, 0.0, 0.0, NEOPIXEL_DELAY_MILLIS, true);
      speaker->playWav("OFF.wav");
      button->setOn(false);
    }
  }
}
