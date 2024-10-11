/*
   LazyGalaxySDCard.cpp - Library for SD Card.
   Created by LazyGalaxy - Evangelos Papakonstantis, September 22, 2024.
   Released into the public domain.
 */

#include <LazyGalaxySDCard.h>

MySDCard::MySDCard(uint8_t pin) : PinComponent(pin)
{
}

void MySDCard::setup()
{
  if (!SD.begin(_pin))
  { // see if the card is present and can be initialized:
    printf("SD fail\n");
    return; // don't do anything more if not
  }
  printf("SD OK\n");
}
