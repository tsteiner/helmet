#ifndef ADAFRUIT_NEOPIXEL_CUSTOM_H
#define ADAFRUIT_NEOPIXEL_CUSTOM_H

#include <Adafruit_NeoPixel.h>

class Adafruit_NeoPixel_Custom : public Adafruit_NeoPixel {
  public:
    Adafruit_NeoPixel_Custom(uint16_t n, uint8_t p=6, uint8_t t=NEO_GRB + NEO_KHZ800);
    void setPixelColor(uint16_t n, uint32_t c, uint8_t a);
};

#endif // ADAFRUIT_NEOPIXEL_H
