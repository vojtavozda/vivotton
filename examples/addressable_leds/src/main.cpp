#include <Arduino.h>
#include <FastLED.h>

#define LEDS_DATA 2
#define LEDS_CLK 1

#define LEDN 25

CRGB FastLED_rgb[LEDN];
CHSV FastLED_hsv[LEDN];

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }
    Serial.println("Addressable LEDs example");

    for (int i=0; i<LEDN; i++) {
		FastLED_hsv[i].h = 0;
		FastLED_hsv[i].s = 0;
		FastLED_hsv[i].v = 0;
        hsv2rgb_spectrum(FastLED_hsv[i],FastLED_rgb[i]);
    }
    FastLED.addLeds<APA102, LEDS_DATA, LEDS_CLK, BGR,DATA_RATE_MHZ(50)>(FastLED_rgb,LEDN);
    FastLED.setBrightness(255);
    FastLED.setDither(0);
    FastLED.show();
}

int loop_count = 0;
int hue = 0;
void loop() {
    // Fill the LEDs with a rainbow effect
    for (int i=0; i<LEDN; i++) {
        FastLED_hsv[i].h = hue + (i * 256 / LEDN);
        FastLED_hsv[i].s = (loop_count % LEDN ) == i ? 0 : 255;
        FastLED_hsv[i].v = (loop_count % LEDN ) == i ? 100 : 20;
        hsv2rgb_spectrum(FastLED_hsv[i],FastLED_rgb[i]);
    }
    FastLED.show();
    
    hue += 5; // Increment hue for the next frame
    if (hue >= 256) {
        hue = 0; // Reset hue after a full cycle
    }
    
    loop_count++;
    delay(100); // Delay to control the speed of the rainbow effect
}