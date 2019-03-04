#include "main.h"

RoastManager g_roast;
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

void registerScreen(Screen *screen) {
    gp_screen = screen;
}

void setup(void) {
    register_i2c_lcd();
    register_max6675();
    register_modbus();
    register_controls();
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
