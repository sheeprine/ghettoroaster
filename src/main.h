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

#ifndef MAIN_H
#define MAIN_H

#include <forward_list>
#include "config.h"
#include "roastmanager.h"
#include "screen.h"
#include "common/display/i2c_lcd.h"
#include "platforms/espressif/common/modbus.h"
#include "common/temp/max6675.h"
#include "platforms/espressif/common/controls.h"
#include "platforms/espressif/common/wifi.h"

void registerInitCallback(void (*func)());
void registerUpdateCallback(void (*func)());
void registerScreen(Screen *screen);

#endif
