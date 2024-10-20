/*
   LazyGalaxySystem.h - The system where are components are registered and managed
   Created by LazyGalaxy - Evangelos Papakonstantis, October 18, 2024.
   Released into the public domain.
 */

#include <LazyGalaxySystem.h>

System::System()
{
}

void System::addComponent(Component *component)
{
  _components.add(component);
}

void System::setupComponents()
{
  for (int i = 0; i < _components.size(); i++)
  {
    Component *component = _components[i];
    component->setup();
    component->reset();
  }
}

void System::loopComponents()
{
  unsigned long time = millis();
  for (int i = 0; i < _components.size(); i++)
  {
    Component *component = _components[i];
    if (component->isActive() && time >= component->_triggerTime)
    {
      DEBUG_VERBOSE("active component with trigger %lu at %lu", component->_triggerTime, time);
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