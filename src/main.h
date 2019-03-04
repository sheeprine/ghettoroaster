#ifndef MAIN_H
#define MAIN_H

// Library dependencies (used by LDF)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

// Thermocouple
#include <max6675.h>
#include <SPI.h>

// Modbus over TCP
#include <ModbusIP_ESP8266.h>

// WiFi configuration manager
#include <WiFiManager.h>

#include "config.h"
#include "platforms/esp8266/config.h"
#include "roastmanager.h"
#include "screen.h"
#include "platforms/esp8266/i2c_lcd.h"

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
