#ifndef ESP8266_MAX6675_H
#define ESP8266_MAX6675_H

#include <max6675.h>
#include <SPI.h>
#include "roastmanager.h"
#include "main.h"

double getETTemp();
double getBTTemp();

void initMAX6675();
void addMAX6675Callbacks();
void register_max6675();

#endif
