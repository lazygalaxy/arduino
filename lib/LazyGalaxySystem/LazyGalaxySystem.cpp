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
    _components[i]->setup();
}

void System::loopComponents()
{
  unsigned long time = millis();
  for (int i = 0; i < _components.size(); i++)
  {
    if (_components[i]->_triggerTime > 0 && time >= _components[i]->_triggerTime)
    {
      _components[i]->_triggerTime = _components[i]->update(time);
      if (_components[i]->_triggerTime == 0)
      {
        if (_components[i]->_finalCallback != nullptr)
          _components[i]->_finalCallback(time);
        if (_components[i]->_triggerTime == 0)
          _components[i]->reset();
      }
    }
  }
}