/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
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
      //   LazyGalaxyTimerTask *temp = current;
      //   if (previous == nullptr) {
      //     head = head->next;
      //     if (head == nullptr) {
      //       tail = nullptr;
      //     }
      //     current = current->next;
      //   } else {
      //     previous->next = current->next;
      //     if (current->next == nullptr) {
      //       tail = current;
      //     }
      //     current = current->next;
      //   }
      //   delete temp;
      current->isActive = false;
      return true;
    }
    // else {
    previous = current;
    current = current->next;
    //}
  }
  return false;
}

void LazyGalaxyTimer::update(unsigned long time) {
  LazyGalaxyTimerTask *current = head;
  LazyGalaxyTimerTask *previous = nullptr;
  while (current != nullptr) {
    Serial.println(String(current->id) + " " + String(current->triggerTime) +
                   " " + String(time));
    // bool remove = false;
    if (current->isActive && current->triggerTime <= time) {
      current->isActive = false;
      if (current->callback != nullptr) {
        current->callback(time);
      } else if (current->component != nullptr) {
        current->triggerTime = current->component->update(time);
        Serial.println("new time: " + String(current->triggerTime));
        if (current->triggerTime > time) {
          current->isActive = true;
        }
      }

      // if (remove) {
      //   LazyGalaxyTimerTask *temp = current;
      //   if (previous == nullptr) {
      //     head = head->next;
      //     if (head == nullptr) {
      //       tail = nullptr;
      //     }
      //     current = current->next;
      //   } else {
      //     previous->next = current->next;
      //     if (current->next == nullptr) {
      //       tail = current;
      //     }
      //     current = current->next;
      //   }
      //   delete temp;
      // }
    }
    // if (!remove) {
    previous = current;
    current = current->next;
    //}
  }
}