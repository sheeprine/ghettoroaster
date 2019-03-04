#include "platforms/esp8266/config.h"
#include "platforms/esp8266/max6675.h"
#include "main.h"

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
    g_roast.addEnvTempFunc(getETTemp);
    g_roast.addBeanTempFunc(getBTTemp);
}

void register_max6675() {
    registerInitCallback(addMAX6675Callbacks);
    registerInitCallback(initMAX6675);
}
