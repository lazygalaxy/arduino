/*
   LightSaber.cpp - LightSaber implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxySystem.h>
#include <LazyGalaxyButton.h>
#include <LazyGalaxyNeoPixel.h>
#include <LazyGalaxySDCard.h>
#include <LazyGalaxySpeaker.h>

static const unsigned int DELAY = 20;
static const float SAT = 1.0;
static const float VAL = 0.5;
static const float k = 0.2;

Button *button = new Button(D5, D4);
MySDCard *sdcard = new MySDCard(D10);
MySpeaker *speaker = new MySpeaker(D9, 5);
NeoPixel *strip = new NeoPixel(D6, 33);

float hue = 0.0;

void motionCallback(unsigned long time, unsigned long accel, unsigned long gyro)
{
  unsigned long COMPL = accel + gyro;
  int freq = (long)COMPL * COMPL / 1500; // parabolic tone change
  freq = constrain(freq, 18, 300);
  int freq_f = freq * k + freq_f * (1 - k); // smooth filter
                                            // speaker.playNote(freq_f);
}

unsigned long changeHueCallback(unsigned long time)
{
  hue += 0.01;
  if (hue > 1.0)
  {
    hue = 0.0;
  }
  strip->setNoSequence(hue, SAT, VAL);

  if (button->isLongPressed())
    return time + 100;

  return time;
}

void setup()
{
  Serial.begin(9600);
  Debug.setDebugLevel(DBG_VERBOSE);

  System::add(button);
  System::add(sdcard);
  System::add(speaker);
  System::add(strip);
  System::setup();
}

void loop()
{
  // first update all tasks
  System::loop();

  // then implement the light saber logic
  if (button->isOff() && button->getClicks() > 0)
  {
    // turn on the light saber with any button click
    button->setOn(true);
    strip->setWipeSequence(hue, SAT, VAL, DELAY, false);
    speaker->playWav("ON.wav");
  }
  else if (button->isOn())
  {
    if (button->isLongPressed())
    {
      // if there is a long press cycle the hue color
      // taskId = Timer::scheduleTask(100, changeHueCallback);
    }
    else if (button->getClicks() == 1)
    {
      // if there is 1 click, stop the light saber
      strip->setWipeSequence(0.0, 0.0, 0.0, DELAY, true);
      speaker->playWav("OFF.wav");
      button->setOn(false);
    }
  }
}
