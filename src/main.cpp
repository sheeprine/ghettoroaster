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

#include "main.h"

RoastManager g_roast;
Screen *gp_screen = nullptr;
#define SLEEP_DELAY 1000/REFRESH_RATE

// Callback lists
std::forward_list<void (*)()> initCallbacks;
std::forward_list<void (*)()> updateCallbacks;

// Drift compensation
unsigned long loopStart;

void registerInitCallback(void (*func)()) {
    initCallbacks.push_front(func);
}

void registerUpdateCallback(void (*func)()) {
    updateCallbacks.push_front(func);
}

void registerScreen(Screen *screen) {
    gp_screen = screen;
}

void setup() {
    register_i2c_lcd();
    register_max6675();
    register_modbus();
    register_controls();
    register_wifi();
    for (auto &callback : initCallbacks)
        (*callback)();
}

void loop() {
    loopStart = millis();
    // Update roast/PID information as soon as possible to minimize drift
    g_roast.tick();
    if (gp_screen)
        gp_screen->setWIFIStatus(WiFi.status() == WL_CONNECTED);
    for (auto &callback : updateCallbacks)
        (*callback)();
    delay(SLEEP_DELAY - millis() - loopStart);
}
