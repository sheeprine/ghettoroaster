#ifndef I2C_SCREEN_H
#define I2C_SCREEN_H

#include "screen.h"

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
        LiquidCrystal_I2C *lcd = NULL;
        void tempStatsScreen(void);
        void outputScreen(void);
        void doRefresh(void);
    public:
        i2cScreen(LiquidCrystal_I2C *i2cLCD);
        ~i2cScreen() {};
};

#endif
