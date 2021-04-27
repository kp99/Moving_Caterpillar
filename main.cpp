#include <Arduino.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define LED_PIN     3
#define NUM_LEDS    46

#define BRIGHTNESS  64

CRGB leds[NUM_LEDS];

CRGBPalette16 currentPalette;

void setupStripedPalette( CRGB A, CRGB B)
{
  currentPalette = CRGBPalette16( 
        A, A, A, A, A, A, A, A, B, B, B, B, B, B, B, B
  );
}

void setup() {
  delay( 1000 );      // power-up safety delay
  FastLED.addLeds<WS2811,LED_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  FastLED.setBrightness(BRIGHTNESS);

  // Color stripes WITH gaps of space (black) between them
  setupStripedPalette( CRGB::Red, CRGB::Black);      // DarkOrange, Red, Green, Yellow, Magenta, Gold, Lime, DodgerBlue
}


void loop()
{
  static uint8_t startIndex = 0;
  startIndex = startIndex - 5;        /* higher = faster motion */ /* + / - for Forward / Backward */

  fill_palette( leds, NUM_LEDS, 
                startIndex, 17,       /* higher = narrower stripes */
                currentPalette, 255, LINEARBLEND);

  FastLED.show();
  FastLED.delay(1000 / 60);
}

//----------------------------------------------------