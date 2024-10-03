/*
   LazyGalaxySDCard.h - Library for SD Card.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 22, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYSDCARD_H
#define LAZYGALAXYSDCARD_H

#include <LazyGalaxyCommon.h>
#include <SD.h>

class MySDCard : public PinComponent
{
public:
  MySDCard(uint8_t pin);
  void setup() override;
};

#endif
