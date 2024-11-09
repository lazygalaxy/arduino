/*
   LazyGalaxyCircuit.h - The circuit where are components are registered and managed
   Created by LazyGalaxy - Evangelos Papakonstantis, October 18, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYCIRCUIT_H
#define LAZYGALAXYCIRCUIT_H

#include <LazyGalaxyCommon.h>
#include <LinkedList.h>

class Circuit
{
private:
  LinkedList<Component *> _components = LinkedList<Component *>();

  Circuit();
  void addComponent(Component *component);
  void setupComponents();
  bool statusOKComponents();
  void loopComponents();

  static Circuit *getInstance()
  {
    static Circuit *systemInstance = new Circuit();
    return systemInstance;
  }

public:
  static void add(Component *component)
  {
    getInstance()->addComponent(component);
  }

  static void setup()
  {
    getInstance()->setupComponents();
  }

  static void loop()
  {
    getInstance()->loopComponents();
  }

  static bool statusOK()
  {
    return getInstance()->statusOKComponents();
  }
};

#endif