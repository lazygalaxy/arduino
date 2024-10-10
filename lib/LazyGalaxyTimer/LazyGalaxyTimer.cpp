/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

Timer::Timer() {}

bool Timer::isDebug() { return _debug; }

void Timer::debugPrint(String message)
{
  if (isDebug())
    Serial.print(message);
}

void Timer::enableDebug()
{
  _debug = true;
  Serial.println("timer debug enabled, id is " + String(idCounter));
}

void Timer::debugPrintln(String message)
{
  if (isDebug())
    Serial.println(message);
}

unsigned long Timer::schedule(unsigned long triggerTime,
                              taskCallbackPtr updateCallback)
{
  TimerTask *task = new TimerTask(++idCounter, triggerTime, updateCallback);
  return schedule(task);
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component)
{
  TimerTask *task = new TimerTask(++idCounter, triggerTime, component);
  return schedule(task);
}

unsigned long Timer::schedule(TimerTask *task)
{
  debugPrintln("add task " + String(task->id) + " " + String(task->triggerTime));
  tasks.put(task);
  debugPrintln("task size now " + String(tasks.elements()));
  return task->id;
}

bool Timer::unschedule(TimerTask *task)
{
  debugPrintln("rem task " + String(task->id) + " " + String(task->triggerTime));
  unsigned int beforeElements = tasks.elements();
  tasks.remove(task);
  delete task;
  task = nullptr;
  debugPrintln("task size now " + String(tasks.elements()));
  return beforeElements > tasks.elements();
}

bool Timer::unschedule(unsigned long taskId)
{
  TimerTask *foundTask = nullptr;
  for (TimerTask *task : tasks)
  {
    if (task->id == taskId)
      foundTask = task;
  }
  if (foundTask != nullptr)
    return unschedule(foundTask);
  return false;
}

void Timer::update(unsigned long time)
{
  TimerTask *foundTask = nullptr;
  for (TimerTask *task : tasks)
  {
    // debugPrintln("task: " + String(task->id) + " " + String(task->isActive) + " " + String(task->triggerTime));

    if (task->triggerTime <= time)
    {
      if (task->updateCallback != nullptr)
        task->updateCallback(time);

      if (task->component != nullptr)
        task->triggerTime = task->component->update(time);

      if (task->triggerTime <= time)
        TimerTask *foundTask = nullptr;
    }
  }
  if (foundTask != nullptr)
    unschedule(foundTask);
}