/*
   LazyGalaxyTimer.h - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYTIMER_H
#define LAZYGALAXYTIMER_H

#include <LazyGalaxyCommon.h>
#include <LazyGalaxyTimerTask.h>

class Timer
{
private:
  unsigned long idCounter = 0;
  SimpleVector<TimerTask *> tasks;

public:
  Timer(char size);
  unsigned long schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback = nullptr);
  unsigned long schedule(unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback = nullptr);
  boolean unschedule(unsigned long taskId);
  void update(unsigned long time);
};

static Timer *timerInstance = new Timer(5);

static long scheduleTask(unsigned int delay, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback = nullptr)
{
  return timerInstance->schedule(millis() + delay, updateCallback, finalCallback);
}

static void updateTasks() { timerInstance->update(millis()); }

#endif