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

unsigned long Timer::schedule(unsigned long triggerTime, updateCallbackPtr updateCallback, char *label)
{
  TimerTask *task = new TimerTask(++idCounter, triggerTime, updateCallback, label);
  return schedule(task);
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component, char *label)
{
  TimerTask *task = new TimerTask(++idCounter, triggerTime, component, label);
  return schedule(task);
}

unsigned long Timer::schedule(TimerTask *task)
{
  printf("add task %s\n", task->label);
  tasks.push_back(task);
  printf("task size now %u\n", tasks.elements());
  return task->id;
}

bool Timer::unschedule(TimerTask *task)
{
  printf("removing task %s %u %i\n", task->label, task->triggerTime, task->active);
  unsigned int beforeElements = tasks.elements();
  tasks.remove(task);
  delete task;
  task = nullptr;
  printf("task size now %u\n", tasks.elements());
  return beforeElements > tasks.elements();
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
  TimerTask *foundTask = nullptr;

  for (TimerTask *task : tasks)
  {
    if (task->triggerTime <= time)
    {
      if (task->updateCallback != nullptr)
        task->triggerTime = task->updateCallback(time);

      if (task->component != nullptr)
        task->triggerTime = task->component->update(time);

      if (!task->active || task->triggerTime <= time)
      {
        printf("to remove task %s %u\n", task->label, time);
        foundTask = task;
      }
    }
  }

  if (foundTask != nullptr)
    unschedule(foundTask);
}