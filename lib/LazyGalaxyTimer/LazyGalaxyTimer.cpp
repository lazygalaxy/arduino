/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

Timer::Timer(char size)
{
  for (char i = 0; i < size; i++)
    tasks.add(new TimerTask(i));
  DEBUG_DEBUG("timer size %i tasks", tasks.size());
}

unsigned long Timer::schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
{
  for (int i = 0; i < tasks.size(); i++)
  {
    TimerTask *task = tasks.get(i);
    if (!task->_active)
    {
      task->setAsUpdateCallback(++idCounter, triggerTime, updateCallback, finalCallback);
      return task->_id;
    }
  }
  DEBUG_ERROR("failed callback task %lu at %lu", idCounter, triggerTime);
  return 0;
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback)
{
  for (int i = 0; i < tasks.size(); i++)
  {
    TimerTask *task = tasks.get(i);
    if (!task->_active)
    {
      task->setAsUpdateComponent(++idCounter, triggerTime, component, finalCallback);
      return task->_id;
    }
  }
  DEBUG_ERROR("failed component task %lu at %lu", idCounter, triggerTime);
  return 0;
}

boolean Timer::unschedule(unsigned long taskId)
{
  for (int i = 0; i < tasks.size(); i++)
  {
    TimerTask *task = tasks.get(i);
    if (task->_id == taskId)
    {
      task->reset();
      return true;
    }
  }
  DEBUG_ERROR("failed to unschedule %lu", taskId);
  return false;
}

void Timer::update(unsigned long time)
{
  for (int i = 0; i < tasks.size(); i++)
  {
    TimerTask *task = tasks.get(i);
    if (task->_active)
    {
      DEBUG_VERBOSE("active task %i with id %lu and trigger %lu at %lu", task->_posi, task->_id, task->_triggerTime, time);
      if (task->_triggerTime <= time)
      {
        if (task->_updateCallback != nullptr)
          task->_triggerTime = task->_updateCallback(time);

        if (task->_component != nullptr)
          task->_triggerTime = task->_component->update(time);

        if (task->_triggerTime <= time)
        {
          if (task->_active)
            task->reset();
          if (task->_finalCallback != nullptr)
            task->_finalCallback(time);
        }
      }
    }
  }
}