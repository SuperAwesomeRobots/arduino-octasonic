#include <Arduino.h>
#include <SPI.h>
#include "octasonic.h"

Octasonic::Octasonic(unsigned int num_sensors) {
  init(num_sensors, 10);
}

Octasonic::Octasonic(unsigned int num_sensors, unsigned int _chipSelect) {
  init(num_sensors, _chipSelect);
}

void Octasonic::init(unsigned int num_sensors, unsigned int _chipSelect) {

  this->chipSelect = _chipSelect;

  pinMode(chipSelect, OUTPUT);
  digitalWrite(chipSelect, HIGH);

  // init SPI
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.begin();

  // set sensor count
  send(0x10 | num_sensors);

}


unsigned int Octasonic::get(unsigned int index) {
  //Serial.println("get_sensor_reading()");
  send(0x30 | index);
  unsigned int ret = send(0x00);
  //Serial.print("get_sensor_reading() returning ");
  //Serial.println(ret);
  return ret;
}

unsigned int Octasonic::send(unsigned int n) {
//  Serial.print("Sending ");
//  Serial.print(n, HEX);
  digitalWrite(chipSelect, LOW);
  unsigned int response = SPI.transfer(n);
  digitalWrite(chipSelect, HIGH);
//  Serial.print(" .. received ");
//  Serial.println(response, HEX);
  return response;
}


