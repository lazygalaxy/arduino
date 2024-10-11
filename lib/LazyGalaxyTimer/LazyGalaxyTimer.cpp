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
  debugPrintln(_debug, 32, "add task %s", 1, task->label);
  tasks.push_back(task);
  debugPrintln(_debug, 32, "task size now %u", 1, tasks.elements());
  return task->id;
}

bool Timer::unschedule(TimerTask *task)
{
  debugPrintln(_debug, 32, "removing task %s %d %d", 3, task->label, task->triggerTime, task->active);
  unsigned int beforeElements = tasks.elements();
  tasks.remove(task);
  delete task;
  task = nullptr;
  debugPrintln(_debug, 32, "task size now %u", 1, tasks.elements());
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
        debugPrintln(_debug, 32, "to remove task %s %d", 2, task->label, time);
        foundTask = task;
      }
    }
  }

  if (foundTask != nullptr)
    unschedule(foundTask);
}