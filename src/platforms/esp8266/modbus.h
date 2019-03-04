#ifndef ESP8266_MODBUS_H
#define ESP8266_MODBUS_H

#include <ModbusIP_ESP8266.h>
#include "roastmanager.h"
#include "main.h"

bool mbToRoastEnabled(void);
double mbToSP(void);
unsigned int mbToFan(void);

void initModbus(void);
void addModbusCallbacks(void);
void populateModbusRegisters(void);
void updateModbus(void);
void register_modbus(void);

#endif
