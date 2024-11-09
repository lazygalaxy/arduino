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
 if (!_sd.begin(_pin, SPI_HALF_SPEED))
 _statusOK= false;
}
