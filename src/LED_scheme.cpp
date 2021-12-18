#include "LED_scheme.h"
#include "Arduino.h"
#include <NeoPixelBus.h>

extern NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

void rainbow(int j) {
  int k = 0;
  int l = 0;
  int m = 0;

  for (int i = 0; i < NUMPIXELS; i++) {
    if ((i >= 0) && (i < NUMPIXELS * 1 / 3)) {
      red = 255 * k / (NUMPIXELS / 3);
      green = 0;
      blue = 255 - (255 * k / (NUMPIXELS / 3));
      k++;
    }
    if ((i >= NUMPIXELS * 1 / 3) && (i < NUMPIXELS * 2 / 3)) {
      red = 255 - (255 * l / (NUMPIXELS / 3));
      green = 255 * l / (NUMPIXELS / 3);
      blue = 0;
      l++;
    }
    if ((i >= NUMPIXELS * 2 / 3) && (i < NUMPIXELS * 3 / 3)) {
      red = 0;
      green = 255 - (255 * m / (NUMPIXELS / 3));
      blue = 255 * m / (NUMPIXELS / 3);
      m++;
    }

    strip.SetPixelColor((i + j) % NUMPIXELS, RgbColor(red, green, blue));
  }

  strip.Show();
  delay(50);
}

void white_shine(int j) {
  int k = 0;
  int l = 0;
  int m = 0;

  for (int i = 0; i < NUMPIXELS; i++) {
    if ((i >= 0) && (i < NUMPIXELS * 1 / 3)) {
      red = 255 * k / (NUMPIXELS / 3);
      green = 255 * k / (NUMPIXELS / 3);
      blue = 255 * k / (NUMPIXELS / 3);
      k++;
    }
    if ((i >= NUMPIXELS * 1 / 3) && (i < NUMPIXELS * 2 / 3)) {
      red = 255 - (255 * l / (NUMPIXELS / 3));
      green = 255 - (255 * l / (NUMPIXELS / 3));
      blue = 255 - (255 * l / (NUMPIXELS / 3));
      l++;
    }
    if ((i >= NUMPIXELS * 2 / 3) && (i < NUMPIXELS * 3 / 3)) {
      red = 0;
      green = 0;
      blue = 0;
      m++;
    }
    Serial.printf("\r\n[R,G,B] = [%d,%d,%d]", red, green, blue);
    strip.SetPixelColor((i + j) % NUMPIXELS, RgbColor(red, green, blue));
  }
  strip.Show();
  delay(40);
}

void red_shine(int j) {
  int k = 0;
  int l = 0;
  int m = 0;

  for (int i = 0; i < NUMPIXELS; i++) {
    if ((i >= 0) && (i < NUMPIXELS * 1 / 3)) {
      red = 255;
      green = 255 - 255 * k / (NUMPIXELS / 3);
      blue = 255 - 255 * k / (NUMPIXELS / 3);
      k++;
    }
    if ((i >= NUMPIXELS * 1 / 3) && (i < NUMPIXELS * 2 / 3)) {
      red = 255;
      green = (255 * l / (NUMPIXELS / 3));
      blue = (255 * l / (NUMPIXELS / 3));
      l++;
    }
    if ((i >= NUMPIXELS * 2 / 3) && (i < NUMPIXELS * 3 / 3)) {
      red = 255;
      green = 255;
      blue = 255;
      m++;
    }
    strip.SetPixelColor((i + j) % NUMPIXELS, RgbColor(red, green, blue));
  }
  strip.Show();
  delay(40);
}

void led_white(int j) {
  for (int i = 0; i < NUMPIXELS; i++) {
    red = 255;
    green = 255;
    blue = 255;
    strip.SetPixelColor((i + j) % NUMPIXELS, RgbColor(red, green, blue));
  }
  delay(5);
  strip.Show();
}

void led_off(int j) {
  for (int i = 0; i < NUMPIXELS; i++) {
    red = 0;
    green = 0;
    blue = 0;
    strip.SetPixelColor((i + j) % NUMPIXELS, RgbColor(red, green, blue));
  }
  delay(100);
  strip.Show();
}

void led_rgb(uint8_t r, uint8_t g, uint8_t b, int j) {
  for (int i = 0; i < NUMPIXELS; i++) {
    red = g;
    green = r;
    blue = b;
    strip.SetPixelColor((i + j) % NUMPIXELS, RgbColor(red, green, blue));
  }
  delay(100);
  strip.Show();
}