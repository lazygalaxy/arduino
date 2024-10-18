/*
   LazyGalaxySystem.h - The system where are components are registered and managed
   Created by LazyGalaxy - Evangelos Papakonstantis, October 18, 2024.
   Released into the public domain.
 */

#include <LazyGalaxySystem.h>

System::System()
{
}

void System::add(Component *component)
{
  _components.add(component);
}

void System::setup()
{
  Serial.begin(9600);
  for (int i = 0; i < _components.size(); i++)
    _components[i]->setup();
}

void System::loop(unsigned long time)
{
  for (int i = 0; i < _components.size(); i++)
  {
    if (_components[i]->_triggerTime > 0 && time >= _components[i]->_triggerTime)
    {
      _components[i]->_triggerTime = _components[i]->update(time);
      if (time >= _components[i]->_triggerTime)
      {
        if (_components[i]->_finalCallback != nullptr)
          _components[i]->_finalCallback(time);
      }
    }
  }
}