/*
   LazyGalaxyTimer.h - Library for scheduling tasks
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

  struct LazyGalaxyTimerTask {
    LazyGalaxyTimerTask(unsigned long id, unsigned long triggerTime,
                        funcPtr callback) {
      this->id = id;
      this->triggerTime = triggerTime;
      this->callback = callback;
      this->component = nullptr;
      this->next = nullptr;
    }

    LazyGalaxyTimerTask(unsigned long id, unsigned long triggerTime,
                        LazyGalaxyComponent* component) {
      this->id = id;
      this->triggerTime = triggerTime;
      this->callback = nullptr;
      this->component = component;
      this->next = nullptr;
    }

    unsigned long id;
    unsigned long triggerTime;
    funcPtr callback;
    LazyGalaxyComponent* component;
    LazyGalaxyTimerTask* next;
  };

  unsigned long schedule(unsigned long triggerTime, funcPtr callback);
  unsigned long schedule(unsigned long triggerTime,
                         LazyGalaxyComponent* component);
  bool unschedule(unsigned long taskId);
  void update(unsigned long time);

 private:
  LazyGalaxyTimer();
  void addTask(LazyGalaxyTimerTask* task);

  unsigned long idCounter = 0;

  LazyGalaxyTimerTask* head = nullptr;
  LazyGalaxyTimerTask* tail = nullptr;
};

#endif