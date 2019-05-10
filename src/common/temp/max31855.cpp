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

#include "common/temp/max31855.h"

#ifdef USE_MAX31855

extern RoastManager g_roast;

Adafruit_MAX31855 *TC_ET = nullptr;
Adafruit_MAX31855 *TC_BT = nullptr;

double getATTemp() {
    return TC_ET->readInternal();
}

double getETTemp() {
    return TC_ET->readCelsius();
}

double getBTTemp() {
    return TC_BT->readCelsius();
}

void initmax31855() {
    SPI.begin();
    TC_ET = new Adafruit_MAX31855(TC_ET_PIN);
    TC_BT = new Adafruit_MAX31855(TC_BT_PIN);
    TC_ET->begin();
    TC_BT->begin();
}

void addmax31855Callbacks() {
    // MAX31855 can go as low as 100ms between temperature readings
    g_roast.setRefreshInterval(100);
    g_roast.addEnvTempFunc(getETTemp);
    g_roast.addBeanTempFunc(getBTTemp);
}

void register_temp() {
    registerInitCallback(addmax31855Callbacks);
    registerInitCallback(initmax31855);
}

#endif
