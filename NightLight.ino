// Libraries
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <RTC.h>

//Leds define parameters: 3 leds, linked ton pin 4
#define NUMPIXELS 3
#define PIN       4

//Instantiate RTC & leds
static DS1307 RTC;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int blue = 255, green = 255, red = 255;

void setup () {
  
//Start led process & set brigthness
  pixels.begin();
  pixels.setBrightness(30);

//Start RTC & serial 
  RTC.begin();
  Serial.begin(9600);
  
}

void loop () {
//Conditions to switch light according to daytime
if (RTC.getHours() >= 20 || RTC.getHours() < 7) {
  blue=255;
  red=0;
  green=0; 
} else if (RTC.getHours() == 7 && RTC.getMinutes() < 30) {
  blue=0;
  red=0;
  green=255;
} else if (RTC.getHours() == 7 && RTC.getMinutes() > 30) {
  blue=255;
  red=255;
  green=255;
} else {
  blue=255;
  red=255;
  green=255;
}
//Display led
  for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(red,green,blue));
      pixels.show(); // This sends the updated pixel color to the hardware.
  }

 //Serial logging to check the code what's going on
  Serial.print("Rouge: ");
  Serial.print(red);
  Serial.print(" Vert: ");
  Serial.print(green);
  Serial.print(" Bleu: ");
  Serial.println(blue);
  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.println(RTC.getSeconds());;
  
  
}
