/*
   LazyGalaxySDCard.h - Library for SD Card.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 22, 2024.
   Released into the public domain.
 */

#ifndef LAZYGALAXYSDCARD_H
#define LAZYGALAXYSDCARD_H

#include <LazyGalaxyCommon.h>
#include <SdFat.h>

class MySDCard : public PinComponent
{
public:
  MySDCard(uint8_t pin);
  void setup() override;

private:
  SdFat _sd;
};

#endif
