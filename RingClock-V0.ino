/*
   Programme RingClock V0
   Preuve de concept
*/
#include "Adafruit_NeoPixel.h"

#define RINGPIN D8 // Broche PWM pour ESP8266 NodeMCU V3 - Compil avec NodeMCU 1.0
#define NBLEDS  60 // Nb de leds de l'anneau
#define OFFSET  29 // Décalage de l'origine (en nombre de leds)

// Définition de l'anneau de leds
Adafruit_NeoPixel pixels(NBLEDS, RINGPIN, NEO_GRB + NEO_KHZ800);

// Cette fonction permet de décaler logiquement l'origine de l'horloge
// Par défaut, la led 0 est au niveau de la connection
int index(int i) {
  return (i + OFFSET) % NBLEDS;
}

// Coloriser une led
void setPixel(int i, uint32_t color) {
  pixels.setPixelColor(index(i), color);
}

// Récupérer la couleur d'une led
uint32_t getPixel(int i) {
  return pixels.getPixelColor(index(i));
}

// Coloriser les 12 marqueurs horaires (en blanc)
void setMarkers(int m) {
  uint32_t markersColor = pixels.Color(50, 50, 50);
  for (int mk = 0; mk < 60; mk+=5) {
    setPixel(mk, markersColor);
  }
}

// Coloriser l'heure courante (en rouge)
void setHours(int h) {
  uint32_t hourColor = pixels.Color(200, 0, 0);
  setPixel(h * 5, hourColor);  // h: 0..11 = 12 Hours
}

// Coloriser la minute courante (en vert)
void setMinutes(int m) {
  uint32_t minColor = pixels.Color(0, 200, 0);
  setPixel(m, minColor);
}

// Coloriser la seconde courante (en bleu)
void setSeconds(int s) {
  uint32_t secColor = pixels.Color(0, 0, 200);
  setPixel(s, secColor);
}

// Afficher les éléments sur le cadran
void showTime(int h, int m, int s) {
  pixels.clear();
  setMarkers(m);
  setMinutes(m);
  setHours(h);
  setSeconds(s);
  pixels.show();
}

// Simuler le temps (50 millisecondes représentent 1 seconde)
void testTime() {
  for (int h = 0; h < 12; h++) {
    for (int m = 0; m < 60; m++) {
      for (int s = 0; s < 60; s++) {
        showTime(h, m, s);
        delay(50);
      }
    }
  }
}

// Initialisation
void setup() {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(10); // luminosité faible = faible consommation + protection occulaire
  pixels.show();
}

// Boucle principale
void loop() {
  testTime(); // le temp qui passe...
}