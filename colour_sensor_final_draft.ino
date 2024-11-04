#include <Wire.h>
#include <FastLED.h>
#include "Adafruit_TCS34725.h"
#define NUM_LEDS 1
#define DATA_PIN 5  //data pin 5 for the arduino RGB colours
#define CLOCK_PIN 13
#define commonAnode false  // set to false if using a common cathode LED
CRGB leds[NUM_LEDS];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); // the colour sensor that is used
// our RGB -> eye-recognized gamma color
byte gammatable[256];




void setup() {

 
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS); //ws2812 is the fastLED libary used for the nanopixel
  Serial.begin(9600);

  if (tcs.begin()) {
    
  }




  for (int i = 0; i < 256; i++) { // it helps convert RGB colors to what humans see
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;
    }
  }
}


void loop() {
  float red, green, blue;


  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);  // turn off LED

  red = red * 1.8;
  if (red > 255) red = 255; //to make red more intense

  green = green * 1.8;
  if (green > 255) green = 255; // to make the green more intense


  blue = blue * 1.8;
  if (blue > 255) blue = 255;  // to make the blue more intense

  Serial.print("R:\t"); Serial.print(uint8_t(red));
  Serial.print("\tG:\t"); Serial.print(uint8_t(green));
  Serial.print("\tB:\t"); Serial.print(uint8_t(blue));

  Serial.print("\t");
  Serial.print((uint8_t)red, HEX); Serial.print((uint8_t)green, HEX); Serial.print((uint8_t)blue, HEX); //prints out data for colours and hex
  Serial.print("\n");

  leds[0] = CRGB(uint8_t(red), uint8_t(green), uint8_t(blue));

  FastLED.show(); //show data on LED

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  Serial.print("R:\t"); Serial.print(uint8_t(red));
  Serial.print("\tG:\t"); Serial.print(uint8_t(green));
  Serial.print("\tB:\t"); Serial.print(uint8_t(blue));
  Serial.println();

}
