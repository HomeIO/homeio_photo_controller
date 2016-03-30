homeio_photo_controller
=======================

TODO:

* monitor current by checking (small resistance) resistor voltage
* monitor voltage
* high voltage capacitor in input (2x max DC input)
* supercapacitor on output as battery replacement (>50F)
* analyze maximum power by performing series of measurements of voltage and current
* 2 PWMs: charging supercapacitor/battery, heater resistor
* charge capacitor/batteries till set voltage (voltage should be changeable remotely)
* optional: third PWM to charge capacitor/batteries to charge them, something like online hybrid UPS

buy:

* 1 MCU: AVR, 3 PWM (hardware preferred), PTH/PDIP connectors
* 100V capacitor
* >50F 18V capacitor
* 3x 0.1 - 0.2 Ohm resistor or current sensor
* PWM NMOS driver
