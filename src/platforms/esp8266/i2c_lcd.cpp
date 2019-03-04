#include "platforms/esp8266/i2c_lcd.h"

extern RoastManager g_roast;

LiquidCrystal_I2C lcd(0x27,16,2);
i2cScreen screen(&lcd);

void register_i2c_lcd() {
  g_roast.addScreen(&screen);
}
