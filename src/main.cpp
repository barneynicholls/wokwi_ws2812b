#include <Arduino.h>
#include <FastLED.h>

// MAX_MILLIWATTS can only be changed at compile-time. Use 0 to disable limit.
// Brightness can be changed at runtime via serial with 'b' and 'B'
#define MAX_MILLIWATTS 0
#define BRIGHTNESS 255
#define LED_PIN 2
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define kMatrixWidth 16
#define kMatrixHeight 1
#define XY_MATRIX (ROWMAJOR)
#define NUM_LEDS ((kMatrixWidth) * (kMatrixHeight))

#define SERIAL_UI 1      // if 1, can be controlled via keypresses in PuTTY
#define FADEIN_FRAMES 32 // how long to reach full brightness when powered on
#define MS_GOAL 20       // to try maintain 1000 / 20ms == 50 frames per second

#define GIF2H_MAX_PALETTE_ENTRIES 140 // RAM is always tight on ATmega328...
#define GIF2H_NUM_PIXELS NUM_LEDS     // all images must be the same size as the matrix

CRGB leds[NUM_LEDS];

int index = 0;

void showStrip()
{
  FastLED.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue)
{
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void FadeInOut(byte red, byte green, byte blue, long fade)
{
  float r, g, b;

  for (int k = 0; k < 256; k = k + 1)
  {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
    delay(fade);
  }

  for (int k = 255; k >= 0; k = k - 2)
  {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
    delay(fade * 2);
  }
}

void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{
  long fade = random(1,15);

  // rgb 255	228	45
  // hex 0xff, 0xe4, 0x2d
  FadeInOut(0xff, 0xe4, 0x2d, fade);

  long pause = random(0, 3000);

  delay(pause);
}
