#ifndef _OCTASONIC_H
#define _OCTASONIC_H

class Octasonic {
public:
  /* init the breakout board */
  Octasonic(unsigned int num_sensors);
  Octasonic(unsigned int num_sensors, unsigned int chipSelect);
  /* get the latest reading for a particular sensor */
  unsigned int get(unsigned int index);

  /* set the interval between polling sensors in intervals of 10 ms up to a maximum of 15 x 10 ms */
  void set_poll_interval(unsigned int n);

private:
  void init(unsigned int num_sensors, unsigned int chipSelect);
  unsigned int send(unsigned int n);
  unsigned int chipSelect;

};

#endif // _OCTASONIC_H
