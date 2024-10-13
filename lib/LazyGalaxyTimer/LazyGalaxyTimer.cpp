/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

Timer::Timer() {}

void Timer::enableDebug()
{
  _debug = true;
}

unsigned long Timer::schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
{
  for (TimerTask *task : tasks)
  {
    if (!task->active)
    {
      task->setAsUpdateCallback(++idCounter, triggerTime, updateCallback, finalCallback);
      printf("add callback task %lu\n", task->id);
      return task->id;
    }
  }
  printf("failed callback task at %lu", idCounter);
  return 0;
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback)
{
  for (TimerTask *task : tasks)
  {
    if (!task->active)
    {
      task->setAsUpdateComponent(++idCounter, triggerTime, component, finalCallback);
      printf("add component task %lu\n", task->id);
      return task->id;
    }
  }
  printf("failed component task at %lu", idCounter);
  return 0;
}

bool Timer::unschedule(unsigned long taskId)
{
  for (TimerTask *task : tasks)
  {
    if (task->id == taskId)
    {
      task->active = false;
      return true;
    }
  }

  return false;
}

void Timer::update(unsigned long time)
{
  for (TimerTask *task : tasks)
  {
    if (task->active && task->triggerTime <= time)
    {
      if (task->updateCallback != nullptr)
        task->triggerTime = task->updateCallback(time);

      if (task->component != nullptr)
        task->triggerTime = task->component->update(time);

      if (task->triggerTime <= time)
      {
        task->active = false;
        if (task->finalCallback != nullptr)
          task->finalCallback(time);
      }
    }
  }
}