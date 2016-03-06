# avr-ultrasonic-breakout

Protocol


Commands from master to slave:
- 1 Set number of sensors (or set bits for enabled ones)
- 2 Set max distance to poll (per sensor)
- 3 Set poll frequency / sleep time between poll
- Set mode (poll serially or in parallel, or test mode)
- Read value for sensors


Master -> slave

1. Configure active sensors

0001 0nnn (where nnnn is sensor count between 1 and 8)

2. Set max distance for sensor

0002 0nnn (where n is sensor number)
followed by 2 bytes for max distance

3.
