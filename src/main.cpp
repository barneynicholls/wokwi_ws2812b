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
#define NUM_LEDS ((kMatrixWidth) * (kMatrixHeight))

CRGB leds[NUM_LEDS];

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

void FadeInOut(byte red, byte green, byte blue, long fade, long pause)
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

  delay(pause);

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
  long fadeSpeed = random(1,15);

  long pauseAtFullBrightness = random(1,1000);

  // rgb 255	228	45
  // hex 0xff, 0xe4, 0x2d
  FadeInOut(255, 228, 45, fadeSpeed, pauseAtFullBrightness);

  long pause = random(0, 3000);

  delay(pause);
}
