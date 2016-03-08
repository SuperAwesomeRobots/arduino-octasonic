#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pinDefines.h"
#include "macros.h"

#define MAX_SENSOR_COUNT 8
unsigned int sensor_count = MAX_SENSOR_COUNT;

volatile unsigned int sensor_data[MAX_SENSOR_COUNT];

void spi_init_slave (void)
{
  SPI_SCK_DDR   &= ~(1 << SPI_SCK);                      /* input on SCK */
  SPI_SS_DDR    &= ~(1 << SPI_SS);                        /* set SS input */
  SPI_MOSI_DDR  &= ~(1 << SPI_MOSI);                   /* input on MOSI */

  SPI_MISO_DDR  |= (1 << SPI_MISO);                   /* output on MISO */
  SPI_MOSI_PORT |= (1 << SPI_MOSI);                  /* pullup on MOSI */

  // enable SPI and SPI interrupt
  SPCR |= ((1 << SPE) | (1 << SPIE));

  SPDR = 0;

  DDRB |= (1 << PB0); // PB0 = output (LED)
}

ISR(SPI_STC_vect) {

  unsigned int data_in = SPDR;

  // first 4 bits are the command number
  unsigned int command = (data_in & 0xF0) >> 4;
  unsigned int index = 0;

  switch (command) {
    case 0:
      SPDR = 0x00;
      break;
    case 1: // set_sensor_count
      sensor_count = data_in & 0x0F;
      SPDR = 0x00;
      break;
    case 2: // get_sensor_count
      SPDR = sensor_count;
      break;
    case 3:
      index = data_in & 0x0F;
      if (index<0 || index>=MAX_SENSOR_COUNT) {
        SPDR = 0xFF;
      } else {
        SPDR = sensor_data[index];
      }
      break;
    default:
      // 0xFF means error condition
      SPDR = 0xFF;
      break;
  }

  // toggle LED
  PORTB ^= (1 << PB0);

}

unsigned int poll_sensor(unsigned int i) {
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

    // stop measuring after 5800 us (100 cm)
    if (count > 5800) {
      break;
    }

  } while (PIND & (1 << i));

  return count / 58;
}

int main(void)
{

  for (int i=0; i<MAX_SENSOR_COUNT; i++) {
    sensor_data[i] = 0;
  }

  spi_init_slave();                             //Initialize slave SPI
  sei();
  while(1) {
    for (int i=0; i<MAX_SENSOR_COUNT; i++) {
      sensor_data[i] = poll_sensor(i);
      _delay_ms(40);
    }
  /*
  PORTB ^= (1 << PB0);
  _delay_ms(500);
  PORTB ^= (1 << PB0);
  _delay_ms(500);
  */
  }
}
