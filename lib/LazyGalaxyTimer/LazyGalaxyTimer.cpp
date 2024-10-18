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
    if (task->_triggerTime == 0)
    {
      task->setAsUpdateCallback(++idCounter, triggerTime, updateCallback, finalCallback);
      return task->_id;
    }
  }
  DEBUG_ERROR("failed callback task %lu at %lu", idCounter, triggerTime);
  return 0;
}

unsigned long Timer::schedule(unsigned long triggerTime, finalCallbackPtr finalCallback)
{
  for (int i = 0; i < tasks.size(); i++)
  {
    TimerTask *task = tasks.get(i);
    if (task->_triggerTime == 0)
    {
      task->setAsFinalCallback(++idCounter, triggerTime, finalCallback);
      return task->_id;
    }
  }
  DEBUG_ERROR("failed callback task %lu at %lu", idCounter, triggerTime);
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
    if (task->_triggerTime > 0)
    {
      DEBUG_VERBOSE("active task %lu and trigger %lu at %lu", task->_id, task->_triggerTime, time);
      if (task->_triggerTime <= time)
      {
        if (task->_updateCallback != nullptr)
          task->_triggerTime = task->_updateCallback(time);

        if (task->_triggerTime <= time)
        {
          if (task->_finalCallback != nullptr)
            task->_finalCallback(time);

          if (task->_triggerTime > 0 && task->_triggerTime <= time)
            task->reset();
        }
      }
    }
  }
}