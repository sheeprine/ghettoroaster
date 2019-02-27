#include "i2c_screen.h"

i2cScreen::i2cScreen(LiquidCrystal_I2C *i2cLCD) {
    lcd = i2cLCD;
    lcd->init();
    lcd->backlight();
    lcd->createChar(0, noWIFI);
    lcd->createChar(1, WIFI);
}

void i2cScreen::tempStatsScreen(void) {
    //  =================
    // |ET:300C  ROR:30.1|
    // |BT:300C  RINT:60s|
    //  =================
    lcd->setCursor(0, 0);
    lcd->print("ET:");
    lcd->print(ET, 0);
    lcd->print(isCelsius ? "C":"F");
    lcd->print("  ");
    lcd->setCursor(8, 0);
    lcd->print("ROR:");
    lcd->print(ROR, 1);
    lcd->print(" ");
    lcd->setCursor(0, 1);
    lcd->print("BT:");
    lcd->print(BT, 0);
    lcd->print(isCelsius ? "C":"F");
    lcd->print("  ");
    lcd->setCursor(8, 1);
    lcd->print("RINT:");
    lcd->print(RINT);
    lcd->print("s");
    lcd->print(" ");
}

void i2cScreen::outputScreen(void) {
    //  =================
    // |FAN:100%  FIN   W|
    // |SP:350C   D:10:30|
    //  =================
    int mins, secs;
    lcd->setCursor(0, 0);
    lcd->print("FAN:");
    lcd->print(fanDutyCycle);
    lcd->print("%");
    lcd->print("  ");
    lcd->setCursor(9, 0);
    switch(roastStatus) {
        case DRY:
            lcd->print("DRY");
            break;
        case TP:
        case MAILL:
            lcd->print("MAILL");
            break;
        case FC:
        case FCE:
        case SC:
        case FIN:
            lcd->print("FIN");
            break;
        case DROP:
            lcd->print("DROP");
            break;
        default:
            lcd->print("STOP");
    }
    lcd->print("  ");
    lcd->setCursor(15, 0);
    lcd->write(wifiEnabled ? 1 : 0);
    lcd->setCursor(0, 1);
    lcd->print("SP:");
    lcd->print(SP, 0);
    lcd->print(isCelsius ? "C":"F");
    lcd->print("  ");
    lcd->setCursor(9, 1);
    lcd->print("D:");
    mins = roastDuration/60;
    if (mins < 10) {
        lcd->print("0");
    }
    lcd->print(mins);
    lcd->print(":");
    secs = roastDuration%60;
    if (secs < 10) {
        lcd->print("0");
    }
    lcd->print(secs);
}

void i2cScreen::doRefresh(void) {
    bool isInterval = roastDuration/3 & 1;
    if (roastStatus != STOPPED && isInterval) {
        if (!onStats)
            lcd->clear();
        onStats = true;
        tempStatsScreen();
    } else {
        if (onStats)
            lcd->clear();
        onStats = false;
        outputScreen();
    }
}
