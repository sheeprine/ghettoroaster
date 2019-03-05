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
        void doRefresh();
    public:
        i2cScreen(LiquidCrystal_I2C *i2cLCD);
        ~i2cScreen() {};
};

#endif
