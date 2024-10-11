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
    TimerTask(unsigned long id, unsigned long triggerTime, updateCallbackPtr updateCallback, char *label)
    {
      this->id = id;
      this->triggerTime = triggerTime;
      this->active = true;
      this->updateCallback = updateCallback;
      this->component = nullptr;
      this->label = label;
    }

    TimerTask(unsigned long id, unsigned long triggerTime, Component *component, char *label)
    {
      this->id = id;
      this->triggerTime = triggerTime;
      this->active = true;
      this->updateCallback = nullptr;
      this->component = component;
      this->label = label;
    }

    ~TimerTask(void)
    {
      this->id = 0;
      this->triggerTime = 0;
      this->active = false;
      this->updateCallback = nullptr;
      this->component = nullptr;
      this->label = nullptr;
    }

    unsigned long id;
    unsigned long triggerTime;
    boolean active;
    updateCallbackPtr updateCallback;
    Component *component;
    char *label;
  };

public:
  static Timer *getInstance()
  {
    static Timer *instance = new Timer();
    return instance;
  }

  static long scheduleTask(unsigned int delay, updateCallbackPtr updateCallback, char *label)
  {
    return getInstance()->schedule(millis() + delay, updateCallback, label);
  }

  static void updateTasks() { getInstance()->update(millis()); }

  void enableDebug();

  unsigned long schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, char *label);
  unsigned long schedule(unsigned long triggerTime, Component *component, char *label);
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