/*
   LazyGalaxyTimer.h - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYTIMER_h
#define LAZYGALAXYTIMER_h

#include <LazyGalaxyCommon.h>

class LazyGalaxyTimer {
 public:
  static LazyGalaxyTimer* getInstance() {
    static LazyGalaxyTimer* instance = new LazyGalaxyTimer();
    return instance;
  }

  static void scheduleTask(unsigned int delay, taskCallbackPtr updateCallback) {
    getInstance()->schedule(millis() + delay, updateCallback);
  }

  static void updateTasks() { getInstance()->update(millis()); }

  struct LazyGalaxyTimerTask {
    LazyGalaxyTimerTask(unsigned long id, unsigned long triggerTime,
                        taskCallbackPtr updateCallback) {
      this->id = id;
      this->triggerTime = triggerTime;
      this->isActive = true;
      this->updateCallback = updateCallback;
      this->component = nullptr;
      this->next = nullptr;
    }

    LazyGalaxyTimerTask(unsigned long id, unsigned long triggerTime,
                        LazyGalaxyComponent* component) {
      this->id = id;
      this->triggerTime = triggerTime;
      this->isActive = true;
      this->updateCallback = nullptr;
      this->component = component;
      this->next = nullptr;
    }

    unsigned long id;
    unsigned long triggerTime;
    bool isActive;
    taskCallbackPtr updateCallback;
    LazyGalaxyComponent* component;
    LazyGalaxyTimerTask* next;
  };

  unsigned long schedule(unsigned long triggerTime,
                         taskCallbackPtr updateCallback);
  unsigned long schedule(unsigned long triggerTime,
                         LazyGalaxyComponent* component);
  bool unschedule(unsigned long taskId);
  void update(unsigned long time);

 private:
  LazyGalaxyTimer();
  void addTask(LazyGalaxyTimerTask* task);
  void cleanTasks();

  unsigned long idCounter = 0;
  LazyGalaxyTimerTask* head = nullptr;
  LazyGalaxyTimerTask* tail = nullptr;
};

#endif