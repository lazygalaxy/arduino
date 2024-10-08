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
  addTask(task);
  return task->id;
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component)
{
  TimerTask *task = new TimerTask(++idCounter, triggerTime, component);
  addTask(task);
  return task->id;
}

void Timer::addTask(TimerTask *task)
{
  debugPrintln("added task " + String(task->id));
  tasks.put(task);
  debugPrintln("task size now " + String(tasks.elements()));
}

bool Timer::unschedule(unsigned long taskId)
{
  for (TimerTask *task : tasks)
  {
    if (task->id == taskId)
    {
      debugPrintln("unschedule task " + String(task->id));
      tasks.remove(task);
      return true;
    }
  }
  return false;
}

void Timer::update(unsigned long time)
{
  // debugPrintln("update tasks " + String(tasks.size()) + " " + String(time));
  for (TimerTask *task : tasks)
  {
    // debugPrintln("task: " + String(task->id) + " " + String(task->isActive) + " " + String(task->triggerTime));

    if (task->triggerTime <= time)
    {
      if (task->updateCallback != nullptr)
      {
        task->updateCallback(time);
        // Serial.println("callback: " + String(time) + " " + String(current->triggerTime));
      }
      if (task->component != nullptr)
      {
        task->triggerTime = task->component->update(time);
        // Serial.println("component: " + String(current->id) + " " + String(time) + " " + String(current->triggerTime));
      }
      if (task->triggerTime <= time)
        tasks.remove(task);
        }
  }
}