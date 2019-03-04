#include "platforms/esp8266/wifi.h"

WiFiManager wManager;

void register_wifi() {
    wManager.autoConnect("GhettoRoaster", "gimmecoffee");
}
