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
  for (int i = 0; i < _components.size(); i++)
  {
    Component *component = _components[i];
    component->setup();
    component->reset();
  }
}

void Circuit::loopComponents()
{
  unsigned long time = millis();
  for (int i = 0; i < _components.size(); i++)
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