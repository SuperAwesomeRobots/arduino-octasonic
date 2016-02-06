#include <SPI.h>
#include "octasonic.h"
#include "notes.h"

int notes[] = {
  NOTE_A4, 
  NOTE_B4, 
  NOTE_C4,
  NOTE_D4,
  NOTE_E4,
  NOTE_F4,
  NOTE_G4
};

const int chipSelectPin = 10;

Octasonic octasonic(8, chipSelectPin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i=0; i<8; i++) {
    int j = octasonic.get(i);
    if (j < 20) {
      tone(9, notes[i]);
      while (octasonic.get(i) < 20) {
        delay(10);
      }
      noTone(9);
    }
  }
}
