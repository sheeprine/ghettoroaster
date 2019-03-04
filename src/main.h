#ifndef MAIN_H
#define MAIN_H

#include <forward_list>
#include "config.h"
#include "platforms/esp8266/config.h"
#include "roastmanager.h"
#include "screen.h"
#include "platforms/esp8266/i2c_lcd.h"
#include "platforms/esp8266/modbus.h"
#include "platforms/esp8266/max6675.h"
#include "platforms/esp8266/wifi.h"

void registerInitCallback(void (*func)(void));
void registerUpdateCallback(void (*func)(void));

// Initialization
void initRoaster(void);
void config(void);
void setup(void);

// Main loop
void loop(void);

#endif
