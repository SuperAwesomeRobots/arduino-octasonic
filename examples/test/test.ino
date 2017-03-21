#include <SPI.h>
#include "octasonic.h"

const int sensorCount = 1;
const int chipSelectPin = 10;

Octasonic octasonic(chipSelectPin);

void setup() {
  Serial.begin(9600);
  
  Serial.print("Protocol version: ");
  Serial.println(octasonic.get_protocol_version());

  octasonic.set_sensor_count(sensorCount);
  
  Serial.print("Sensor count: ");
  Serial.println(octasonic.get_sensor_count());
}

void loop() {
  
  for (int i=0; i<sensorCount; i++) {
    int j = octasonic.get_sensor_reading(i);

    // print number with leading spaces if required
    if (j<100) Serial.print(" ");
    if (j<10) Serial.print(" ");
    Serial.print(j);

    Serial.print("  ");
  }
  Serial.println();
  delay(1000);
}