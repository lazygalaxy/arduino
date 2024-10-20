/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

Timer::Timer()
{
}

unsigned long Timer::scheduleTask(unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
{
  TimerTask *task = new TimerTask(++idCounter);
  task->setAsUpdateCallback(++idCounter, triggerTime, updateCallback, finalCallback);
  tasks.add(task);
  return task->_id;
}

unsigned long Timer::scheduleTask(unsigned long triggerTime, finalCallbackPtr finalCallback)
{
  TimerTask *task = new TimerTask(++idCounter);
  task->setAsFinalCallback(++idCounter, triggerTime, finalCallback);
  tasks.add(task);
  return task->_id;
}

void Timer::updateTasks(unsigned long time)
{
  for (int i = 0; i < tasks.size(); i++)
  {
    TimerTask *task = tasks.get(i);
    if (task->_triggerTime <= time)
    {
      if (task->_updateCallback != nullptr)
        task->_triggerTime = task->_updateCallback(time);

      if (task->_triggerTime <= time)
      {
        if (task->_finalCallback != nullptr)
          task->_finalCallback(time);

        tasks.remove(i);
        break;
      }
    }
  }
}