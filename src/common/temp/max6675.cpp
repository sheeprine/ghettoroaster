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

#include "common/temp/max6675.h"

#ifdef USE_MAX6675

extern RoastManager g_roast;

MAX6675 TC_ET;
MAX6675 TC_BT;

double getETTemp() {
    return TC_ET.readCelsius();
}

double getBTTemp() {
    return TC_BT.readCelsius();
}

void initMAX6675() {
    SPI.begin();
    TC_ET.begin(TC_ET_PIN);
    TC_BT.begin(TC_BT_PIN);
}

void addMAX6675Callbacks() {
    // MAX6675 temperature readings refresh is between 170 to 200ms
    g_roast.setRefreshInterval(180);
    g_roast.addEnvTempFunc(getETTemp);
    g_roast.addBeanTempFunc(getBTTemp);
}

void register_temp() {
    registerInitCallback(addMAX6675Callbacks);
    registerInitCallback(initMAX6675);
}

#endif
