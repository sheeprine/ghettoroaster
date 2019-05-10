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
#include "platforms/espressif/common/config.h"
#include "roastmanager.h"
#include "config.h"
#include "main.h"

#ifdef USE_HEATER_PWM
#ifdef USE_ZC_SSR
#include <core_esp8266_waveform.h>

#define HEATER_PWM_FREQ 10
#define FREQ_PERIOD 1E6/HEATER_PWM_FREQ
#endif
#endif

#define DUTY_STEP PWMRANGE/100

void setFan(unsigned int dutyCycle);
#ifndef USE_HEATER_PWM
void setHeater(bool enabled);
#else
void setHeaterPWM(unsigned int val);
#endif
void register_controls();

#endif
