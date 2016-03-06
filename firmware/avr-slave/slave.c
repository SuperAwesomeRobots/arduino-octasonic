#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pinDefines.h"
#include "macros.h"

#define max_sensor_count 8

unsigned int sensor_count = max_sensor_count;
unsigned int poll_interval_us = 50;

volatile unsigned int sensor_data[max_sensor_count];

void spi_init_slave (void)
{
  SPI_SCK_DDR &= ~(1 << SPI_SCK);                      /* input on SCK */
  SPI_SS_DDR &= ~(1 << SPI_SS);                        /* set SS input */
  SPI_MOSI_DDR &= !(1 << SPI_MOSI);                   /* input on MOSI */

  SPI_MISO_DDR |= (1 << SPI_MISO);                   /* output on MISO */

  SPI_MOSI_PORT |= (1 << SPI_MOSI);                  /* pullup on MOSI */

  SPCR |= (1 << SPE);                                        /* enable */
}

//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
  SPDR = data;                                  //Load data into buffer
  while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
  return(SPDR);                                 //Return received data
}

int poll_sensor(unsigned int i) {

  // trigger
  DDRD |= (1 << i);
  PORTD |= (1 << i);
  _delay_us(10);
  PORTD &= ~(1 << i);

  // set pin to input
  DDRD &= ~(1 << i);

  // loop while echo is LOW
  unsigned int count = 0;
  do {
    if (++count > 1000) {
      break;
    }
  } while (!(PIND & (1 << i)));

  // loop while echo is HIGH
  count = 0;
  do {
    count = count + 1;
    _delay_us(1);

    if (count > 5800) {
      break;
    }

  } while (PIND & (1 << i));

  return count / 58;

}

int main(void)
{
  // init state to zero
  for (int i=0; i<max_sensor_count; i++) {
    sensor_data[i] = 0;
  }

  spi_init_slave();                             //Initialize slave SPI

  while(1) {

    // take sensor readings
    for (int i=0; i<max_sensor_count; i++) {
      sensor_data[i] = poll_sensor(i);
    }

    unsigned int data_in = spi_tranceiver(0);

    // first 4 bits are the command number
    unsigned int command = (data_in & 0xF0) >> 4;

    switch (command) {
      case 0:
        // ignore
        break;
      case 1: // set_sensor_count
        sensor_count = data_in & 0x0F;
        break;
      case 2: // get_sensor_count
        spi_tranceiver(sensor_count);
        break;
      case 3: // get_sensor_reading
        spi_tranceiver(sensor_data[data_in & 0x0F]);
        break;
      default:
        // 0xFF means error condition
        spi_tranceiver(0xFF);
        break;
    }

  }
}
