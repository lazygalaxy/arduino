/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimerTask.h>

TimerTask::TimerTask(char posi)
{
  _posi = posi;
  reset();
  _finalCallback = nullptr;
}

void TimerTask::setAsUpdateCallback(unsigned long id, unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
{
  _id = id;
  _triggerTime = triggerTime;
  _active = true;
  _updateCallback = updateCallback;
  _finalCallback = finalCallback;
  _component = nullptr;
  DEBUG_DEBUG("set callback task %i with id %lu at %lu", _posi, _id, _triggerTime);
}

void TimerTask::setAsUpdateComponent(unsigned long id, unsigned long triggerTime, Component *component, finalCallbackPtr finalCallback)
{
  _id = id;
  _triggerTime = triggerTime;
  _active = true;
  _updateCallback = nullptr;
  _component = component;
  _finalCallback = finalCallback;
  DEBUG_DEBUG("set component task %i with id %lu at %lu", _posi, _id, _triggerTime);
}

void TimerTask::setAsFinalCallback(unsigned long id, unsigned long triggerTime, finalCallbackPtr finalCallback)
{
  _id = id;
  _triggerTime = triggerTime;
  _active = true;
  _updateCallback = nullptr;
  _component = nullptr;
  _finalCallback = finalCallback;
  DEBUG_DEBUG("set final task %i with id %lu at %lu", _posi, _id, _triggerTime);
}

void TimerTask::reset()
{
  DEBUG_DEBUG("reset task %i with id %lu", _posi, _id);
  _id = 0;
  _triggerTime = 0;
  _active = false;
  _updateCallback = nullptr;
  _finalCallback = nullptr;
  _component = nullptr;
}