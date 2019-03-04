#include "controls.h"

extern RoastManager g_roast;

void setFan(unsigned int dutyCycle) {
    // Convert to 8 bits resolution
    analogWrite(FAN_PWN_PIN, dutyCycle*25.5);
}
void setHeater(bool enabled) {
    digitalWrite(HEATER_PIN, enabled);
}

void initControls(void) {
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(FAN_PWN_PIN, OUTPUT);
}

void addControlCallbacks(void) {
    g_roast.addFanSetDutyFunc(setFan);
    g_roast.addHeaterEnabledFunc(setHeater);
}

void register_controls(void) {
    registerInitCallback(initControls);
    registerInitCallback(addControlCallbacks);
}
