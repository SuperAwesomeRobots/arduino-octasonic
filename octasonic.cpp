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
  send(0x30 | index);
  return send(0x00);
}

/* set the interval between polling sensors in intervals of 10 ms up to a maximum of 15 x 10 ms */
void Octasonic::set_poll_interval(unsigned int n) {
  send(0x34 | n);
  return send(0x00);

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


