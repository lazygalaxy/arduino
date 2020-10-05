/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

Timer::Timer() {}

unsigned long Timer::schedule(unsigned long triggerTime,
                              taskCallbackPtr updateCallback) {
  TimerTask *task = new TimerTask(++idCounter, triggerTime, updateCallback);
  addTask(task);
  return task->id;
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component) {
  TimerTask *task = new TimerTask(++idCounter, triggerTime, component);
  addTask(task);
  return task->id;
}

void Timer::addTask(TimerTask *task) {
  if (head == nullptr) {
    head = task;
    tail = task;
  } else {
    tail->next = task;
    tail = task;
  }
}

void Timer::cleanTasks() {
  TimerTask *current = head;
  TimerTask *previous = nullptr;
  while (current != nullptr) {
    if (!current->isActive) {
      TimerTask *temp = current;
      if (previous == nullptr) {
        head = head->next;
        if (head == nullptr) {
          tail = nullptr;
        }
        current = current->next;
      } else {
        previous->next = current->next;
        if (current->next == nullptr) {
          tail = current;
        }
        current = current->next;
      }
      delete temp;
    } else {
      previous = current;
      current = current->next;
    }
  }
}

bool Timer::unschedule(unsigned long taskId) {
  TimerTask *current = head;
  while (current != nullptr) {
    if (current->id == taskId) {
      current->isActive = false;
      return true;
    }
    current = current->next;
  }
  return false;
}

void Timer::update(unsigned long time) {
  // Serial.println(String(time));

  TimerTask *current = head;
  while (current != nullptr) {
    if (current->isActive && current->triggerTime <= time) {
      if (current->updateCallback != nullptr) {
        current->updateCallback(time);
        // Serial.println("callback: " + String(time) + " " +
        // String(current->triggerTime));
      }
      if (current->component != nullptr) {
        current->triggerTime = current->component->update(time);
        // Serial.println("component: " + String(time) + " " +
        // String(current->triggerTime));
      }
      if (current->triggerTime <= time) {
        current->isActive = false;
      }
    }
    current = current->next;
  }
  cleanTasks();
}