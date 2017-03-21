#include <Arduino.h>
#include <SPI.h>
#include "octasonic.h"

#define CMD_GET_PROTOCOL_VERSION 0x01
#define CMD_SET_SENSOR_COUNT     0x02
#define CMD_GET_SENSOR_COUNT     0x03
#define CMD_GET_SENSOR_READING   0x04
#define CMD_SET_INTERVAL         0x05
#define CMD_TOGGLE_LED           0x06

Octasonic::Octasonic(unsigned int num_sensors, unsigned int _chipSelect) {
  this->chipSelect = _chipSelect;

  pinMode(chipSelect, OUTPUT);
  digitalWrite(chipSelect, HIGH);

  // init SPI
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.begin();

  // set sensor count
  //send(CMD_SET_SENSOR_COUNT << 4 | num_sensors);

}

/*
unsigned int Octasonic::get_protocol_version() {
  return sendAndReceive(CMD_GET_PROTOCOL_VERSION << 4);
}

unsigned int Octasonic::get_sensor_count() {
  return sendAndReceive(CMD_GET_SENSOR_COUNT << 4);
}

void Octasonic::toggle_led() {
  send(CMD_TOGGLE_LED);
}

unsigned int Octasonic::get(unsigned int index) {
  return sendThenReceive(CMD_GET_SENSOR_READING << 4 | index);
}
*/

/* set the interval between polling sensors in intervals of 10 ms up to a maximum of 15 x 10 ms */
/*void Octasonic::set_poll_interval(unsigned int n) {
  send(CMD_SET_INTERVAL << 4 | n);
}
*/


/*
unsigned int Octasonic::sendThenReceive(unsigned int n) {
  digitalWrite(chipSelect, LOW);
  SPI.transfer(n);
  unsigned int response = SPI.transfer(0x00);
  digitalWrite(chipSelect, HIGH);
  return response;
}

unsigned int Octasonic::send(unsigned int n) {
  digitalWrite(chipSelect, LOW);
  unsigned int response = SPI.transfer(n);
  digitalWrite(chipSelect, HIGH);
  return response;
}

*/

