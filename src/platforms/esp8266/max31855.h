/*
Copyright 2019 Stephane Albert

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef ESP8266_MAX31855_H
#define ESP8266_MAX31855_H

#include "platforms/esp8266/config.h"

#ifdef USE_MAX31855

#include <Adafruit_MAX31855.h>
#include <SPI.h>
#include "roastmanager.h"
#include "main.h"

double getATTemp();
double getETTemp();
double getBTTemp();

void initmax31855();
void addmax31855Callbacks();
void register_max31855();

#endif
#endif
