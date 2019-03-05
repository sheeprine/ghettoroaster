#include "main.h"

RoastManager g_roast;
Screen *gp_screen = nullptr;

// Callback lists
std::forward_list<void (*)()> initCallbacks;
std::forward_list<void (*)()> updateCallbacks;

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
    if (gp_screen)
        gp_screen->setWIFIStatus(WiFi.status() == WL_CONNECTED);
    g_roast.tick();
    for (auto &callback : updateCallbacks)
        (*callback)();
    delay(1000/REFRESH_RATE);
}
