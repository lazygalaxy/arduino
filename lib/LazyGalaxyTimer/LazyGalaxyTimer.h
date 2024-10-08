/*
   LazyGalaxyTimer.h - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYTIMER_H
#define LAZYGALAXYTIMER_H

#include <LazyGalaxyCommon.h>

class Timer
{
public:
  static Timer *getInstance()
  {
    static Timer *instance = new Timer();
    return instance;
  }

  static long scheduleTask(unsigned int delay, taskCallbackPtr updateCallback)
  {
    return getInstance()->schedule(millis() + delay, updateCallback);
  }

  static void updateTasks() { getInstance()->update(millis()); }

  bool isDebug();
  void debugPrint(String message);
  void debugPrintln(String message);
  void enableDebug();

  unsigned long schedule(unsigned long triggerTime,
                         taskCallbackPtr updateCallback);
  unsigned long schedule(unsigned long triggerTime, Component *component);
  bool unschedule(unsigned long taskId);
  void update(unsigned long time);

private:
  bool _debug;
  struct TimerTask
  {
    TimerTask(unsigned long id, unsigned long triggerTime,
              taskCallbackPtr updateCallback)
    {
      this->id = id;
      this->triggerTime = triggerTime;
      this->isActive = true;
      this->updateCallback = updateCallback;
      this->component = nullptr;
      this->next = nullptr;
    }

    TimerTask(unsigned long id, unsigned long triggerTime,
              Component *component)
    {
      this->id = id;
      this->triggerTime = triggerTime;
      this->isActive = true;
      this->updateCallback = nullptr;
      this->component = component;
      this->next = nullptr;
    }

    unsigned long id;
    unsigned long triggerTime;
    bool isActive;
    taskCallbackPtr updateCallback;
    Component *component;
    TimerTask *next;
  };

  Timer();
  void addTask(TimerTask *task);
  void cleanTasks();

  unsigned long idCounter = 0;
  TimerTask *head = nullptr;
  TimerTask *tail = nullptr;
};

#endif