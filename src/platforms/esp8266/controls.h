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

#ifndef ESP8266_CONTROLS_H
#define ESP8266_CONTROLS_H

#include <Arduino.h>
#include "platforms/esp8266/config.h"
#include "roastmanager.h"
#include "main.h"

#define DUTY_STEP PWMRANGE/100

void setFan(unsigned int dutyCycle);
void setHeater(bool enabled);
void register_controls();

#endif
