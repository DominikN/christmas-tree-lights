#ifndef LED_SCHEME
#define LED_SCHEME

#include "Arduino.h"

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 12

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 60

void rainbow(int j);
void white_shine(int j);
void red_shine(int j);
void led_white(int j=0);
void led_off(int j=0);
void led_rgb(uint8_t r, uint8_t g, uint8_t b, int j=0);

#endif