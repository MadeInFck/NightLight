/*****************************************
  Horloge ATTiny85
  Un module LED&KEY à base de TM1638 et
  une horloge temps réel DS1307 sont
  branchés au ATTiny85.
  L'horloge affiche la date et l'heure grâce
  à l'afficheur 8 chiffres.  Les LEDs permettent
  d'indiquer le jour de la semaine, et les 
  boutons permettent de changer la date et l'heure.
  
  Pour plus de détails:
  http://electroniqueamateur.blogspot.com/2017/10/une-horloge-base-dattiny85.html
  
******************************************/

// Bibliothèques
//#include <TinyWireM.h>   // bibliothèque i2c pour ATTiny
//#include <TinyRTClib.h>  // bibliothèque horloge temps réel pour ATTiny
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <RTC.h>
// #include <TinyWireM.h>
// #include <TinyRTClib.h>

#define NUMPIXELS 3
#define PIN       4

static DS1307 RTC;
//RTC_DS1307 RTC;        // initialisation de l'horloge temps réel

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int blue = 255, green = 255, red = 255;

void setup () {

  //TinyWireM.begin();            // Initialisation I2C
  //RTC.begin();                  // Initialisation de l'horloge DS1307
  pixels.begin();
  
  Serial.begin(9600);
  RTC.begin();

  Serial.println();
  Serial.println("*** RTC 1307 ***");
  Serial.print("Is Clock Running : ");
  if (RTC.isRunning())
    Serial.println("Yes");
  else
    Serial.println("No. Time may be Inaccurate");
  Serial.print("Hour Mode : ");
  if (RTC.getHourMode() == CLOCK_H24)
    Serial.println("24 Hours");
  else
    Serial.println("12 Hours");
  Serial.print("Is Out Pin Enabled : ");
  if (RTC.isOutPinEnabled())
    Serial.println("Yes");
  else
    Serial.println("No");

  Serial.print("Is SQWE Enabled : ");
  if (RTC.isSqweEnabled())
    Serial.println("Yes");
  else
    Serial.println("No");

}

void loop () {

 switch (RTC.getWeek())
  {
    case 1:
      Serial.print("SUN");
      break;
    case 2:
      Serial.print("MON");
      break;
    case 3:
      Serial.print("TUE");
      break;
    case 4:
      Serial.print("WED");
      break;
    case 5:
      Serial.print("THU");
      break;
    case 6:
      Serial.print("FRI");
      break;
    case 7:
      Serial.print("SAT");
      break;
  }
  Serial.print(" ");
  Serial.print(RTC.getDay());
  Serial.print("-");
  Serial.print(RTC.getMonth());
  Serial.print("-");
  Serial.print(RTC.getYear());

  Serial.print(" ");

  Serial.print(RTC.getHours());
  Serial.print(":");
  Serial.print(RTC.getMinutes());
  Serial.print(":");
  Serial.print(RTC.getSeconds());
  if (RTC.getHourMode() == CLOCK_H12)
  {
    switch (RTC.getMeridiem())
    {
      case HOUR_AM :
        Serial.print(" AM");
        break;
      case HOUR_PM :
        Serial.print(" PM");
        break;
    }
  }
  Serial.println();

if (RTC.getHours() > 22 || RTC.getHours() < 6) {
  blue=255;
  red=0;
  green=0; 
} else if (RTC.getHours() >= 6 && RTC.getHours() < 7) {
  blue=0;
  red=255;
  green=0;
} else if (RTC.getHours() >= 7 && RTC.getHours() < 9) {
  blue=0;
  red=0;
  green=255;
} else {
  blue=255;
  red=255;
  green=255;
}

  for(int i=0;i<NUMPIXELS;i++){

      pixels.setPixelColor(i, pixels.Color(red,green,blue));

      pixels.show(); // This sends the updated pixel color to the hardware.

     
  }
  Serial.print("Rouge: ");
  Serial.print(red);
  Serial.print(" Vert: ");
  Serial.print(green);
  Serial.print(" Bleu: ");
  Serial.println(blue);
  
  delay(1000);
}
