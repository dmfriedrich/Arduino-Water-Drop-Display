#include <FastLED.h>

#define LED_PIN     6   // Microcontroller Pin
#define LED_COUNT  93   // Total LED count

CRGB leds[LED_COUNT];

  int lowerLim = 20;  //This should never be set above upper
  int upperLim = 200; //Never below lower
  int hue = 45;       //Color of lights based on HSU
  int sat = 255;      //intensity of Lights, dim is controlled via visibility so unimportant for function
  int hues[] = {upperLim, 150, 100, 75, 50, lowerLim}; //Starting brightness levels for each ring, preferably equal segments between upper and lower
                                                       //Have as many hues as you do checkpoints-1
  boolean rings[] = {true, false, false, false, false, false};  //Initial direction of brightness adjustment. I set these to false initially besides the outer ring as the ring is one large pulse,
                                                                //making smaller pulse waves could require code reconstruction.
  int checkpoints[] = {0, 32, 56, 72, 84, 92, 93};        //Starting LED of each ring for full ring selection. If changing remember the last
                                                          //checkpoint is the final LED of the final ring, so in the current case where the last
                                                          //ring is 1 LED, the cap is 93 and the startpoint is 92.
void setup() {
  
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  FastLED.clear();
  for (int i = 0; i < (sizeof(checkpoints)/sizeof(checkpoints[0]))-1; i++) {
    setupHelper(i);
  }
}

//Could be a nested loop but used a helper function for clarity
void setupHelper(int ring) {
    for (int i = checkpoints[ring]; i < checkpoints[ring+1]; i++) {
    leds[i] = CHSV(hue, sat, hues[ring]);
  }
}

void loop() {

  for (int i = 0; i < sizeof(rings); i++) {
      pulse(rings[i], checkpoints[i]);
  }
  
  FastLED.show();
  delay(3);
}

void pulse(boolean ring, int checkpoint) {

  int current = 0;

  for(int i = 0; i < (sizeof(checkpoints)/sizeof(checkpoints[0])) - 1; i++) {
        if(checkpoints[i] == checkpoint) {
            current = i;
            break;
        }
    }

        if (hues[current] > upperLim) {
        rings[current] = false;
        hues[current] = upperLim;
      }
      else if (hues[current] < lowerLim) {
        rings[current] = true;
        hues[current] = lowerLim;
      }
      else {
        if (rings[current] == true) {
          hues[current] = hues[current] + 1;
        }
        else {
          hues[current] = hues[current] - 1;
          }
      }
      for (int i = checkpoints[current]; i < checkpoints[current+1]; i++) {
            leds[i] = CHSV(hue, sat, hues[current]);

      }
    }