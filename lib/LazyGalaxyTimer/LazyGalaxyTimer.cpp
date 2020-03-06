/*
   LazyGalaxyTimer.cpp - Library for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

LazyGalaxyTimer::LazyGalaxyTimer() {}

unsigned long LazyGalaxyTimer::schedule(unsigned long triggerTime,
                                        funcPtr callback) {
  LazyGalaxyTimerTask *task =
      new LazyGalaxyTimerTask(++idCounter, triggerTime, callback);
  addTask(task);
  return task->id;
}

unsigned long LazyGalaxyTimer::schedule(unsigned long triggerTime,
                                        LazyGalaxyComponent *component) {
  LazyGalaxyTimerTask *task =
      new LazyGalaxyTimerTask(++idCounter, triggerTime, component);
  addTask(task);
  return task->id;
}

void LazyGalaxyTimer::addTask(LazyGalaxyTimerTask *task) {
  if (head == nullptr) {
    head = task;
    tail = task;
  } else {
    tail->next = task;
    tail = task;
  }
}

bool LazyGalaxyTimer::unschedule(unsigned long taskId) {
  LazyGalaxyTimerTask *current = head;
  LazyGalaxyTimerTask *previous = nullptr;
  while (current != nullptr) {
    if (current->id == taskId) {
      LazyGalaxyTimerTask *temp = current;
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

void LazyGalaxyTimer::update(unsigned long time) {
  LazyGalaxyTimerTask *current = head;
  LazyGalaxyTimerTask *previous = nullptr;
  while (current != nullptr) {
    bool remove = false;
    if (current->triggerTime <= time) {
      remove = true;
      if (current->callback != nullptr) {
        current->callback(time);
      } else if (current->component != nullptr) {
        unsigned int delay = current->component->update(time);
        if (delay > 0) {
          remove = false;
          current->triggerTime = time + delay;
        }
      }

      if (remove) {
        LazyGalaxyTimerTask *temp = current;
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