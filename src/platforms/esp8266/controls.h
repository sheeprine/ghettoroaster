#ifndef ESP8266_CONTROLS_H
#define ESP8266_CONTROLS_H

#include <Arduino.h>
#include "platforms/esp8266/config.h"
#include "roastmanager.h"
#include "main.h"

void setFan(unsigned int dutyCycle);
void setHeater(bool enabled);
void register_controls();

#endif
