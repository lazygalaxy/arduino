/*
   LazyGalaxyTimerTask.h - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#ifndef LAZYGALAXYTIMERTASK_H
#define LAZYGALAXYTIMERTASK_H

#include <LazyGalaxyCommon.h>

class TimerTask
{
public:
  unsigned long _id = 0;
  unsigned long _triggerTime = 0;
  updateCallbackPtr _updateCallback = nullptr;
  finalCallbackPtr _finalCallback = nullptr;

  TimerTask(char posi);
  void setAsUpdateCallback(unsigned long id, unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback);
  void setAsFinalCallback(unsigned long id, unsigned long triggerTime, finalCallbackPtr finalCallback);
  void reset();
};

#endif