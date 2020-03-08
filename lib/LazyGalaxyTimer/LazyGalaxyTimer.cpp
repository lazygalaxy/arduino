/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimer.h>

LazyGalaxyTimer::LazyGalaxyTimer() {}

unsigned long LazyGalaxyTimer::schedule(unsigned long triggerTime,
                                        taskCallbackPtr updateCallback) {
  LazyGalaxyTimerTask *task =
      new LazyGalaxyTimerTask(++idCounter, triggerTime, updateCallback);
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

void LazyGalaxyTimer::cleanTasks() {
  LazyGalaxyTimerTask *current = head;
  LazyGalaxyTimerTask *previous = nullptr;
  while (current != nullptr) {
    if (!current->isActive) {
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
    } else {
      previous = current;
      current = current->next;
    }
  }
}

bool LazyGalaxyTimer::unschedule(unsigned long taskId) {
  LazyGalaxyTimerTask *current = head;
  while (current != nullptr) {
    if (current->id == taskId) {
      current->isActive = false;
      return true;
    }
    current = current->next;
  }
  return false;
}

void LazyGalaxyTimer::update(unsigned long time) {
  LazyGalaxyTimerTask *current = head;
  while (current != nullptr) {
    if (current->isActive && current->triggerTime <= time) {
      if (current->updateCallback != nullptr) {
        current->updateCallback(time);
      }
      if (current->component != nullptr) {
        current->triggerTime = current->component->update(time);
      }
      if (current->triggerTime <= time) {
        current->isActive = false;
      }
    }
    current = current->next;
  }
  cleanTasks();
}