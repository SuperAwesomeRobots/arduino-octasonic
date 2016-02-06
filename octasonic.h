#ifndef _OCTASONIC_H
#define _OCTASONIC_H

class Octasonic {
public:
  /* init the breakout board */
  Octasonic(unsigned int num_sensors);
  Octasonic(unsigned int num_sensors, unsigned int chipSelect);
  /* get the latest reading for a particular sensor */
  unsigned int get(unsigned int index);

private:
  unsigned int chipSelect;

};

#endif // _OCTASONIC_H
