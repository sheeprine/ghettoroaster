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
    analogWrite(FAN_PWM_PIN, dutyCycle*DUTY_STEP);
}

#ifndef USE_HEATER_PWM
void setHeater(bool enabled) {
    digitalWrite(HEATER_PIN, enabled);
}
#else
#ifdef USE_ZC_SSR
void setHeaterPWM(unsigned int val) {
    // FIXME(sheeprine): Assume that PID max is 255
    unsigned long highTime = val*FREQ_PERIOD/255;
    startWaveform(HEATER_PIN, highTime, FREQ_PERIOD-highTime, 0);
}
#else
void setHeaterPWM(unsigned int val) {
    analogWrite(HEATER_PIN, dutyCycle*DUTY_STEP);
}
#endif
#endif

void initControls() {
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(FAN_PWM_PIN, OUTPUT);
}

void addControlCallbacks() {
    g_roast.addSetFanDutyFunc(setFan);
#ifndef USE_HEATER_PWM
    g_roast.addHeaterEnabledFunc(setHeater);
#else
    g_roast.addHeaterPWMFunc(setHeaterPWM);
#endif
}

void register_controls() {
    registerInitCallback(initControls);
    registerInitCallback(addControlCallbacks);
}
