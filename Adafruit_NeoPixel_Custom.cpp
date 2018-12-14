#include "Adafruit_NeoPixel_Custom.h"

// Just call the parent constructor
Adafruit_NeoPixel_Custom::Adafruit_NeoPixel_Custom(uint16_t n, uint8_t p=6, uint8_t t=NEO_GRB + NEO_KHZ800) :
  Adafruit_NeoPixel(n, p, t)
{
    //void
}

// Set color with an additional brightness parameter.
void Adafruit_NeoPixel_Custom::setPixelColor(uint16_t n, uint32_t c, uint8_t a)
{
  uint8_t
    r = (uint8_t)(c >> 16),
    g = (uint8_t)(c >>  8),
    b = (uint8_t)c;

  r = (r * a) >> 8;
  g = (g * a) >> 8;
  b = (b * a) >> 8;

  Adafruit_NeoPixel::setPixelColor(n, r, g, b);
}
