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
    g_roast.addFanSetDutyFunc(setFan);
    g_roast.addHeaterEnabledFunc(setHeater);
}

void register_controls() {
    registerInitCallback(initControls);
    registerInitCallback(addControlCallbacks);
}
