/*
   LightSaber.cpp - LightSaber implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyButton.h>
#include <LazyGalaxyMotion.h>
#include <LazyGalaxyNeoPixel.h>
#include <LazyGalaxySDCard.h>
#include <LazyGalaxySpeaker.h>

static const unsigned int DELAY = 20;
static const float SAT = 1.0;
static const float VAL = 0.5;
static const float k = 0.2;

Button button(D5, D4);
MySDCard sdcard(D10);
MySpeaker speaker(D9, 5);
NeoPixel strip(D6, 33);

long taskId = -1;
float hue = 0.0;
boolean humEnable = false;

void motionCallback(unsigned long time, unsigned long accel, unsigned long gyro)
{
  if (humEnable)
  {
    unsigned long COMPL = accel + gyro;
    int freq = (long)COMPL * COMPL / 1500; // parabolic tone change
    freq = constrain(freq, 18, 300);
    int freq_f = freq * k + freq_f * (1 - k); // smooth filter
    // speaker.playNote(freq_f);
  }
}

// MyMotion motion(100);

void changeHueCallback(unsigned long time)
{
  if (taskId != -1)
  {
    hue += 0.01;
    if (hue > 1.0)
    {
      hue = 0.0;
    }
    strip.setNoSequence(hue, SAT, VAL);
    taskId = -1;
  }
}

void setup()
{
  Serial.begin(9600);

  sdcard.setup();
  strip.setup();
  // motion.setup();
}

void completeOff()
{
  button.setOn(false);
}

void completeOn()
{
  humEnable = true;
}

void loop()
{
  // first update all tasks
  Timer::updateTasks();

  // then implement the light saber logic
  if (button.isOff() && button.getClicks() > 0)
  {
    // turn on the light saber with any button click
    button.setOn(true);
    strip.setWipeSequence(hue, SAT, VAL, DELAY, false);
    speaker.playWav("ON.wav", completeOn);
  }
  else if (button.isOn())
  {
    if (button.isLongPressed())
    {
      // if there is a long press cycle the hue color
      if (taskId == -1)
        taskId = Timer::scheduleTask(100, changeHueCallback);
    }
    else if (button.getClicks() == 1)
    {
      // if there is 1 click, stop the light saber
      strip.setWipeSequence(0.0, 0.0, 0.0, DELAY, true);
      humEnable = false;
      speaker.playWav("OFF.wav", completeOff);
    }
    else
    {
      // if there is no button press
      taskId = -1;
    }
  }
}
