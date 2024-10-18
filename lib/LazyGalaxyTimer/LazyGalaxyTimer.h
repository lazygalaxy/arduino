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
  void update(unsigned long time);

public:
  unsigned long schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback = nullptr);
  unsigned long schedule(unsigned long triggerTime, finalCallbackPtr finalCallback);
  boolean unschedule(unsigned long taskId);

  static Timer *getInstance()
  {
    static Timer *timerInstance = new Timer(3);
    return timerInstance;
  }

  static long scheduleTask(unsigned int delay, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
  {
    return getInstance()->schedule(millis() + delay, updateCallback, finalCallback);
  }

  static long scheduleTask(unsigned int delay, finalCallbackPtr finalCallback)
  {
    return getInstance()->schedule(millis() + delay, finalCallback);
  }

  static void updateTasks() { getInstance()->update(millis()); }
};

#endif