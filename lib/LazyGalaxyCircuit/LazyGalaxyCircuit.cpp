/*
   LazyGalaxyCircuit.h - The system where are components are registered and managed
   Created by LazyGalaxy - Evangelos Papakonstantis, October 18, 2024.
   Released into the public domain.
 */

#include <LazyGalaxyCircuit.h>

Circuit::Circuit()
{
}

void Circuit::addComponent(Component *component)
{
  _components.add(component);
}

void Circuit::setupComponents()
{
  for (uint8_t i = 0; i < _components.size(); i++)
  {
    Component *component = _components[i];
    component->setup();
    component->reset();
  }
  if (!statusOKComponents())
    Serial.println(F("circuit error"));
  else
    Serial.println(F("circuit ok"));
}

bool Circuit::statusOKComponents()
{
  for (uint8_t i = 0; i < _components.size(); i++)
    if (!_components[i]->_statusOK)
      return false;
  return true;
}

void Circuit::loopComponents()
{
  unsigned long time = millis();
  for (uint8_t i = 0; i < _components.size(); i++)
  {
    Component *component = _components[i];
    if (component->isActive() && time >= component->_triggerTime)
    {
      component->_triggerTime = component->update(time);
      if (!component->isActive())
      {
        if (component->_finalCallback != nullptr)
          component->_finalCallback(time);
        if (!component->isActive())
          component->reset();
      }
    }
  }
}