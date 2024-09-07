/*
   LightSaber.cpp - LightSaber implementation.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 6, 2024.
   Released into the public domain.
*/

#include <LazyGalaxyButton.h>
#include <LazyGalaxyNeoPixel.h>

static const unsigned int DELAY = 10;
static const float SAT = 1.0;
static const float VAL = 0.5;

Button button(D2, D3);
NeoPixel strip(D11, 33);

long taskId = -1;
float hue = 0.0;

void turnOnFinalCallback(unsigned long time)
{
}

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
  strip.setup();
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
    strip.setWipeSequence(hue, SAT, VAL, DELAY, false, turnOnFinalCallback);
  }
  else if (button.isOn())
  {
    if (button.isLongPressed())
    {
      // if there is a long press cycle the hue color
      if (taskId == -1)
      {
        taskId = Timer::scheduleTask(100, changeHueCallback);
      }
    }
    else if (button.getClicks() == 1)
    {
      // if there is 1 click, stop the light saber
      strip.off();
      button.setOn(false);
    }
    else
    {
      // if there is no button press
      taskId = -1;
    }
  }
}
