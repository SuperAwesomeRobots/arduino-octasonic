#include "pitches.h"


#include <SPI.h>

const int chipSelectPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.begin();
}

unsigned int send(unsigned int n) {
//  Serial.print("Sending ");
//  Serial.print(n, HEX);
  digitalWrite(chipSelectPin, LOW);
  unsigned int response = SPI.transfer(n);
  digitalWrite(chipSelectPin, HIGH);
//  Serial.print(" .. received ");
//  Serial.println(response, HEX);
  return response;
}

void set_sensor_count(unsigned int count) {
  Serial.print("set_sensor_count() count=");
  Serial.println(count);
  send(0x10 | count);
}

unsigned int get_sensor_count() {
  Serial.println("get_sensor_count()");
  send(0x20);
  unsigned int ret = send(0x00);
  Serial.print("get_sensor_count() returning ");
  Serial.println(ret);
  return ret;
}

unsigned int get_sensor_reading(unsigned int index) {
  //Serial.println("get_sensor_reading()");
  send(0x30 | index);
  unsigned int ret = send(0x00);
  //Serial.print("get_sensor_reading() returning ");
  //Serial.println(ret);
  return ret;
}


void loop() {
  for (int i=0; i<8; i++) {
    Serial.print(get_sensor_reading(i));
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);
}
