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

#include "controls.h"

extern RoastManager g_roast;

void setFan(unsigned int dutyCycle) {
    // Convert to 8 bits resolution
    analogWrite(FAN_PWM_PIN, dutyCycle*25.5);
}
void setHeater(bool enabled) {
    digitalWrite(HEATER_PIN, enabled);
}

void initControls() {
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(FAN_PWM_PIN, OUTPUT);
}

void addControlCallbacks() {
    g_roast.addSetFanDutyFunc(setFan);
    g_roast.addHeaterEnabledFunc(setHeater);
}

void register_controls() {
    registerInitCallback(initControls);
    registerInitCallback(addControlCallbacks);
}
