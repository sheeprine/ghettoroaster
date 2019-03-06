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

#ifndef I2C_SCREEN_H
#define I2C_SCREEN_H

#include "screen.h"

#include <cstdio>
#include <cstdlib>

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const char WIFI[8] = {
    0b00000,
    0b01110,
    0b10001,
    0b00100,
    0b01010,
    0b00000,
    0b00100,
    0b00000,
};

const char noWIFI[8] = {
    0b00001,
    0b01110,
    0b10011,
    0b00100,
    0b01110,
    0b01000,
    0b01100,
    0b10000,
};


class i2cScreen : public Screen {
    private:
        char m_tempStatsScreenBuffer[2][17];
        char m_outputScreenBuffer[2][17];
        LiquidCrystal_I2C *mp_lcd = nullptr;
        unsigned int doubleLen(double num);
        void tempStatsScreen();
        void outputScreen();
        void doRefresh() override;
    public:
        i2cScreen(LiquidCrystal_I2C *i2cLCD);
        ~i2cScreen() override {};
};

#endif
