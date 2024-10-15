/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

Timer::Timer(size_t size)
{
  TimerTask storage_array[size];
  tasks.setStorage(storage_array, size, size);
  DEBUG_DEBUG("timer with size %i", tasks.size());
}

unsigned long Timer::schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
{
  for (TimerTask task : tasks)
  {
    if (!task._active)
    {
      task.setAsUpdateCallback(++idCounter, triggerTime, updateCallback, finalCallback);
      DEBUG_DEBUG("add callback task %lu at %lu", task._id, task._triggerTime);
      return task._id;
    }
  }
  DEBUG_ERROR("failed callback task %lu at %lu", idCounter, triggerTime);
  return 0;
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback)
{
  for (TimerTask task : tasks)
  {
    if (!task._active)
    {
      task.setAsUpdateComponent(++idCounter, triggerTime, component, finalCallback);
      DEBUG_DEBUG("add component task %lu at %lu", task._id, task._triggerTime);
      return task._id;
    }
  }
  DEBUG_ERROR("failed component task %lu", idCounter, triggerTime);
  return 0;
}

bool Timer::unschedule(unsigned long taskId)
{
  for (TimerTask task : tasks)
  {
    if (task._id == taskId)
    {
      task._active = false;
      return true;
    }
  }

  return false;
}

void Timer::update(unsigned long time)
{
  for (TimerTask task : tasks)
  {
    if (task._active)
    {
      DEBUG_VERBOSE("check task %lu with trigger %lu at %lu", task._id, task._triggerTime, time);
      if (task._triggerTime <= time)
      {
        if (task._updateCallback != nullptr)
          task._triggerTime = task._updateCallback(time);

        if (task._component != nullptr)
          task._triggerTime = task._component->update(time);

        if (task._triggerTime <= time)
        {
          task._active = false;
          if (task._finalCallback != nullptr)
            task._finalCallback(time);
        }
      }
    }
  }
}