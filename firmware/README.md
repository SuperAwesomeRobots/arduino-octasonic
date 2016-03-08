# Octasonic Breakout Firmware

## Instructions

To upload new firmware to the board you will need an [AVR Pocket Programmer](https://www.sparkfun.com/products/9825).

From the command-line, type the following:

```
cd avr-slave-interrupt
make flash
```

## Protocol

The current protocol is very simple and uses single byte requests and responses. The first four bits of each request indicate the command, as follows:

- 0001 - Set number of sensors (last four bits specify number of sensors)
- 0002 - Query number of sensors
- 0003 - Get latest reading for a sensor (last four bits specify sensor index)

## Planned enhancements

I plan on making the following improvements soon:

- Add command to set max distance to read (currently hard-coded as 100cm)
- Use two bytes for sensor readings, allowing for distances > 255 cm
- Make the polling interval configurable
- Make the polling order configurable




