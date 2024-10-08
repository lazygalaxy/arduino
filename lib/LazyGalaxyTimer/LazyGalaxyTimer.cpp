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
  // debugPrintln("schedule callback task " + String(idCounter + 1));
  TimerTask *task = new TimerTask(++idCounter, triggerTime, updateCallback);
  addTask(task);
  return task->id;
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component)
{
  // debugPrintln("schedule component task " + String(idCounter + 1));
  TimerTask *task = new TimerTask(++idCounter, triggerTime, component);
  addTask(task);
  return task->id;
}

void Timer::addTask(TimerTask *task)
{
  debugPrintln("added task " + String(task->id));
  if (head == nullptr)
  {
    head = task;
    tail = task;
  }
  else
  {
    tail->next = task;
    tail = task;
  }
}

void Timer::cleanTasks()
{
  TimerTask *current = head;
  TimerTask *previous = nullptr;
  while (current != nullptr)
  {
    if (!current->isActive)
    {
      TimerTask *temp = current;
      if (previous == nullptr)
      {
        head = head->next;
        if (head == nullptr)
        {
          tail = nullptr;
        }
        current = current->next;
      }
      else
      {
        previous->next = current->next;
        if (current->next == nullptr)
        {
          tail = current;
        }
        current = current->next;
      }
      debugPrintln("delete task " + String(temp->id));
      delete temp;
    }
    else
    {
      previous = current;
      current = current->next;
    }
  }
}

bool Timer::unschedule(unsigned long taskId)
{
  TimerTask *current = head;
  while (current != nullptr)
  {
    if (current->id == taskId)
    {
      current->isActive = false;
      debugPrintln("inactive task " + String(current->id));
      return true;
    }
    current = current->next;
  }
  return false;
}

void Timer::update(unsigned long time)
{
  TimerTask *current = head;
  while (current != nullptr)
  {
    // Serial.println("task: " + String(current->id) + " " + String(current->isActive) + " " + String(time) + " " + String(current->triggerTime));

    if (current->isActive && current->triggerTime <= time)
    {
      if (current->updateCallback != nullptr)
      {
        current->updateCallback(time);
        // Serial.println("callback: " + String(time) + " " + String(current->triggerTime));
      }
      if (current->component != nullptr)
      {
        current->triggerTime = current->component->update(time);
        // Serial.println("component: " + String(current->id) + " " + String(time) + " " + String(current->triggerTime));
      }
      if (current->triggerTime <= time)
      {
        current->isActive = false;
      }
    }
    current = current->next;
  }
  cleanTasks();
}