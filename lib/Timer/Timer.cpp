/*
   Timer.cpp - Library for scheduling tasks using a timer.
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <Timer.h>

Timer::Timer() {}

unsigned long Timer::schedule(unsigned long triggerTime, funcPtr callback) {
  TimerTask *task = new TimerTask(triggerTime, callback);
  addTask(task);
  return task->id;
}

unsigned long Timer::schedule(unsigned long triggerTime, Component *component) {
  TimerTask *task = new TimerTask(triggerTime, component);
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

bool Timer::unschedule(unsigned long taskId) {
  TimerTask *current = head;
  TimerTask *previous = nullptr;
  while (current != nullptr) {
    if (current->id == taskId) {
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
      return true;
    } else {
      previous = current;
      current = current->next;
    }
  }
  return false;
}

void Timer::update(unsigned long time) {
  TimerTask *current = head;
  TimerTask *previous = nullptr;
  while (current != nullptr) {
    bool remove = false;
    if (current->triggerTime <= time) {
      remove = true;
      if (current->callback != nullptr) {
        current->callback();
      } else if (current->component != nullptr) {
        unsigned int delay = current->component->update(time);
        if (delay > 0) {
          remove = false;
          current->triggerTime = time + delay;
        }
      }

      if (remove) {
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
      }
    }
    if (!remove) {
      previous = current;
      current = current->next;
    }
  }
}