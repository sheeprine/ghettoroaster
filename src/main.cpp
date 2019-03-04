#include "main.h"

RoastManager g_roast;
Roaster *roasterState = g_roast.getRoasterState();
// FIXME(sheeprine): Unused, will be populated at a later stage of the
// refactoring
Screen *gp_screen = NULL;

// Callback lists
std::forward_list<void (*)(void)> initCallbacks;
std::forward_list<void (*)(void)> updateCallbacks;

void registerInitCallback(void (*func)(void)) {
    initCallbacks.push_front(func);
}

void registerUpdateCallback(void (*func)(void)) {
    updateCallbacks.push_front(func);
}

void setFan(unsigned int dutyCycle) { analogWrite(FAN_PWN_PIN, dutyCycle); }
void setHeater(bool enabled) { digitalWrite(HEATER_PIN, enabled); }

void initRoaster(void) {
    g_roast.addFanSetDutyFunc(setFan);
    g_roast.addHeaterEnabledFunc(setHeater);
}

void config(void) {
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(FAN_PWN_PIN, OUTPUT);
}

void setup(void) {
    config();
    // Map to 0-100%
    analogWriteRange(100);
    register_i2c_lcd();
    register_max6675();
    initRoaster();
    register_modbus();
    register_wifi();
    for (auto it = initCallbacks.begin(); it != initCallbacks.end(); ++it)
        (*it)();
}

void loop(void) {
    if (gp_screen)
        gp_screen->setWIFIStatus(WiFi.status() == WL_CONNECTED);
    g_roast.tick();
    for (auto it = updateCallbacks.begin(); it != updateCallbacks.end(); ++it)
        (*it)();
    delay(1000/REFRESH_RATE);
}
