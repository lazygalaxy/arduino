/*
   LazyGalaxySystem.h - The system where are components are registered and managed
   Created by LazyGalaxy - Evangelos Papakonstantis, October 18, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYSYSTEM_H
#define LAZYGALAXYSYSTEM_H

#include <LazyGalaxyCommon.h>
#include <LinkedList.h>

class System
{
private:
  LinkedList<Component *> _components = LinkedList<Component *>();

  System();

public:
  void add(Component *component);
  void setup();
  void loop(unsigned long time);

  static System *getInstance()
  {
    static System *systemInstance = new System();
    return systemInstance;
  }
};

#endif