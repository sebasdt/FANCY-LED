#include <FastLED.h>


// if LEDs are arranged as a matrix, put the number of rows in 'height' and number of columns in 'width'
const int height = 14;
const int width = 14;
int coords[width][height];

#define NUM_LEDS height*width

CRGB leds[NUM_LEDS];
void setup() {
  // put your setup code here, to run once:

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS); // Initalize LEDs

  FastLED.clear(true); // clear all LEDs and push to strip (makes it all black)

  mapXY();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("sine begin");
  EVERY_N_MILLISECONDS(30) hue++;
  for (int x = 0; x <  width; x++) {
    int  y = map(sin16(millis() * 16 + x * 3500), -32768, 32767, 0, height - 1);
    leds[coords[x][y]] = CHSV(hue, 255, 255);
  }
  fadeAll(255);
  FastLED.show();
  //Serial.println("sine end");
}

void fadeAll(int fadeVar) {
  for (int i = 0; i < NUM_LEDS; i++) leds[i].nscale8(fadeVar);
}

void mapXY() {
  static int index = 0; // Keeps track of which LED is next

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (i % 2 == 0) { // If it's going towards the right
        coords[j][i] = index; // The LED we're on is applied to that (x,y) coordinate
        index++;
      }
      else { // If it's going towards the left
        coords[width - 1 - j][i] = index;
        index++;
      }
    }
  }
}
