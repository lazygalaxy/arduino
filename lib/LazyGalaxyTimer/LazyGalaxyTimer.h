/*
   LazyGalaxyTimer.h - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYTIMER_H
#define LAZYGALAXYTIMER_H

#include <LazyGalaxyCommon.h>
#include <Vector.h>

class Timer
{
private:
  struct TimerTask
  {
    void setAsUpdateCallback(unsigned long id, unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
    {
      _id = id;
      _triggerTime = triggerTime;
      _active = true;
      _updateCallback = updateCallback;
      _finalCallback = finalCallback;
      _component = nullptr;
    }

    void setAsUpdateComponent(unsigned long id, unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback)
    {
      _id = id;
      _triggerTime = triggerTime;
      _active = true;
      _updateCallback = nullptr;
      _finalCallback = finalCallback;
      _component = component;
    }

    unsigned long _id;
    unsigned long _triggerTime;
    boolean _active;
    updateCallbackPtr _updateCallback;
    finalCallbackPtr _finalCallback;
    Component *_component;
  };

public:
  static Timer *getInstance()
  {
    static Timer *instance = new Timer(5);
    return instance;
  }

  static long scheduleTask(unsigned int delay, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback = nullptr)
  {
    return getInstance()->schedule(millis() + delay, updateCallback, finalCallback);
  }

  static void updateTasks() { getInstance()->update(millis()); }

  unsigned long schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback = nullptr);
  unsigned long schedule(unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback = nullptr);
  bool unschedule(unsigned long taskId);
  void update(unsigned long time);

private:
  unsigned long idCounter = 0;
  Vector<TimerTask> tasks;

  Timer(size_t size);
};

#endif