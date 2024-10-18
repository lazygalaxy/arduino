/*
   LazyGalaxyTimer.h - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYTIMER_H
#define LAZYGALAXYTIMER_H

#include <LazyGalaxyTimerTask.h>
#include <LinkedList.h>

class Timer
{
private:
  unsigned long idCounter = 0;
  LinkedList<TimerTask *> tasks = LinkedList<TimerTask *>();

  Timer(char size);
  unsigned long scheduleTask(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback = nullptr);
  unsigned long scheduleTask(unsigned long triggerTime, finalCallbackPtr finalCallback);
  void updateTask(unsigned long time);

  static Timer *getInstance()
  {
    static Timer *timerInstance = new Timer(3);
    return timerInstance;
  }

public:
  static long schedule(unsigned int delay, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
  {
    return getInstance()->scheduleTask(millis() + delay, updateCallback, finalCallback);
  }

  static long schedule(unsigned int delay, finalCallbackPtr finalCallback)
  {
    return getInstance()->scheduleTask(millis() + delay, finalCallback);
  }

  static void update() { getInstance()->updateTask(millis()); }
};

#endif