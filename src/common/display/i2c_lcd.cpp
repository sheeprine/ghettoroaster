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

#include "common/display/i2c_lcd.h"

extern RoastManager g_roast;

LiquidCrystal_I2C lcd(0x27, 16, 2);
i2cScreen screen(&lcd);

void register_i2c_lcd() {
  g_roast.addScreen(&screen);
  registerScreen(&screen);
  lcd.setCursor(0, 0);
  lcd.print(" GhettoRoaster ");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
}
