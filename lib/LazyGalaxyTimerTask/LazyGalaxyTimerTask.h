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
  char _posi;
  boolean _active;
  unsigned long _id = 0;
  unsigned long _triggerTime;
  updateCallbackPtr _updateCallback;
  finalCallbackPtr _finalCallback;
  Component *_component;

  TimerTask(char posi);
  void setAsUpdateCallback(unsigned long id, unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback);
  void setAsUpdateComponent(unsigned long id, unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback);
  void setAsFinalCallback(unsigned long id, unsigned long triggerTime, finalCallbackPtr finalCallback);
  void reset();
};

#endif