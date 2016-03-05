#include <SPI.h>
#include "octasonic.h"

const int chipSelectPin = 10;

Octasonic octasonic(8, chipSelectPin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  for (int i=0; i<8; i++) {
    int j = octasonic.get(i);
    Serial.print(j);
    Serial.print("  ");
  }
  Serial.println();
}
