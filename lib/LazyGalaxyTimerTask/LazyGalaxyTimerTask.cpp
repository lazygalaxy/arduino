/*
   LazyGalaxyTimer.cpp - Util for scheduling tasks
   Created by LazyGalaxy - Evangelos Papakonstantis, Febraury 1, 2020.
   Released into the public domain.
 */

#include <LazyGalaxyTimerTask.h>

TimerTask::TimerTask(char posi)
{
  reset();
}

void TimerTask::setAsUpdateCallback(unsigned long id, unsigned long triggerTime, updateCallbackPtr updateCallback, finalCallbackPtr finalCallback)
{
  _id = id;
  _triggerTime = triggerTime;
  _updateCallback = updateCallback;
  _finalCallback = finalCallback;
  DEBUG_DEBUG("set callback task %lu at %lu", _id, _triggerTime);
}

void TimerTask::setAsFinalCallback(unsigned long id, unsigned long triggerTime, finalCallbackPtr finalCallback)
{
  _id = id;
  _triggerTime = triggerTime;
  _updateCallback = nullptr;
  _finalCallback = finalCallback;
  DEBUG_DEBUG("set final task %lu at %lu", _id, _triggerTime);
}

void TimerTask::reset()
{
  DEBUG_DEBUG("reset task %lu", _id);
  _id = 0;
  _triggerTime = 0;
  _updateCallback = nullptr;
  _finalCallback = nullptr;
}