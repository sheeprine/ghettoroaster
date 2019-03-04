#ifndef MAIN_H
#define MAIN_H

#include <forward_list>

// Thermocouple
#include <max6675.h>
#include <SPI.h>

// Modbus over TCP
#include <ModbusIP_ESP8266.h>

#include "config.h"
#include "platforms/esp8266/config.h"
#include "roastmanager.h"
#include "screen.h"
#include "platforms/esp8266/i2c_lcd.h"
#include "platforms/esp8266/wifi.h"

void registerInitCallback(void (*func)(void));
void registerUpdateCallback(void (*func)(void));

// Helpers
bool mbToRoastEnabled(void);
double mbToSP(void);
unsigned int mbToFan(void);
double getETTemp(void);
double getBTTemp(void);

// Initialization
void initMAX6675(void);
void initModbus(void);
void initRoaster(void);
void config(void);
void setup(void);

// Main loop
void populateModbusRegisters(void);
void loop(void);

#endif
