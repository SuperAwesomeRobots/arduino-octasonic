#include <SPI.h>
#include "octasonic.h"

const int sensorCount = 1;
const int chipSelectPin = 10;

Octasonic octasonic(sensorCount, chipSelectPin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  for (int i=0; i<sensorCount; i++) {
    int j = octasonic.get(i);
    Serial.print(j);
    Serial.print("  ");
  }
  Serial.println();
  delay(1000);
}
