#ifndef ESP8266_MODBUS_H
#define ESP8266_MODBUS_H

#include <ModbusIP_ESP8266.h>
#include "roastmanager.h"
#include "main.h"

bool mbToRoastEnabled();
double mbToSP();
unsigned int mbToFan();

void initModbus();
void addModbusCallbacks();
void populateModbusRegisters();
void updateModbus();
void register_modbus();

#endif
