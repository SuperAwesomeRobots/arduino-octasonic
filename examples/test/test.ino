#include <SPI.h>
#include "octasonic.h"

const int sensorCount = 1;
const int chipSelectPin = 10;

Octasonic octasonic(chipSelectPin);

void setup() {
  Serial.begin(9600);
  
  octasonic.set_sensor_count(sensorCount);
}

void loop() {
  
  for (int i=0; i<sensorCount; i++) {
    int j = octasonic.get(i);

    // print number with leading spaces if required
    if (j<100) Serial.print(" ");
    if (j<10) Serial.print(" ");
    Serial.print(j);

    Serial.print("  ");
  }
  Serial.println();
  delay(100);
}
