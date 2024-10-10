/*
   LazyGalaxyTimer.h - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYTIMER_H
#define LAZYGALAXYTIMER_H

#include <LazyGalaxyCommon.h>
#include <SimpleVector.h>

class Timer
{
private:
  struct TimerTask
  {
    TimerTask(unsigned long id, unsigned long triggerTime,
              taskCallbackPtr updateCallback)
    {
      this->id = id;
      this->triggerTime = triggerTime;
      this->updateCallback = updateCallback;
      this->component = nullptr;
    }

    TimerTask(unsigned long id, unsigned long triggerTime,
              Component *component)
    {
      this->id = id;
      this->triggerTime = triggerTime;
      this->updateCallback = nullptr;
      this->component = component;
    }

    ~TimerTask(void)
    {
      this->id = 0;
      this->triggerTime = 0;
      this->updateCallback = nullptr;
      this->component = nullptr;
    }

    unsigned long id;
    unsigned long triggerTime;
    taskCallbackPtr updateCallback;
    Component *component;
  };

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
  Timer();
  unsigned long schedule(TimerTask *task);
  bool unschedule(TimerTask *task);

  unsigned long idCounter = 0;
  SimpleVector<TimerTask *> tasks;
};

#endif