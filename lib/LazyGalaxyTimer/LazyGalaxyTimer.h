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
    TimerTask(unsigned long id, unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
    {
      this->id = id;
      this->triggerTime = triggerTime;
      this->active = true;
      this->updateCallback = updateCallback;
      this->finalCallback = finalCallback;
      this->component = nullptr;
    }

    TimerTask(unsigned long id, unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback)
    {
      this->id = id;
      this->triggerTime = triggerTime;
      this->active = true;
      this->updateCallback = nullptr;
      this->finalCallback = finalCallback;
      this->component = component;
    }

    ~TimerTask(void)
    {
      this->id = 0;
      this->triggerTime = 0;
      this->active = false;
      this->updateCallback = nullptr;
      this->finalCallback = nullptr;
      this->component = nullptr;
    }

    unsigned long id;
    unsigned long triggerTime;
    boolean active;
    updateCallbackPtr updateCallback;
    finalCallbackPtr finalCallback;
    Component *component;
  };

public:
  static Timer *getInstance()
  {
    static Timer *instance = new Timer();
    return instance;
  }

  static long scheduleTask(unsigned int delay, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback = nullptr)
  {
    return getInstance()->schedule(millis() + delay, updateCallback, finalCallback);
  }

  static void updateTasks() { getInstance()->update(millis()); }

  void enableDebug();

  unsigned long schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback = nullptr);
  unsigned long schedule(unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback = nullptr);
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