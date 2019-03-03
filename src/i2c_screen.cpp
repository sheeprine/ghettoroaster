#include "i2c_screen.h"

i2cScreen::i2cScreen(LiquidCrystal_I2C *i2cLCD) {
    lcd = i2cLCD;
    lcd->init();
    lcd->backlight();
    lcd->createChar(0, noWIFI);
    lcd->createChar(1, WIFI);
}

unsigned int i2cScreen::doubleLen(double num) {
    if (num >= 100)
        return 3;
    if (num >= 10)
        return 2;
    return 1;
}

void i2cScreen::tempStatsScreen(void) {
    //  =================
    // |ET:300C  ROR:30.1|
    // |BT:300C  RINT:60s|
    //  =================
    const char sign = isCelsius ? 'C':'F';
    sprintf(tempStatsScreenBuffer[0], "ET:%.0f%-*c  ROR:%-*.1f",
            ET, 4-doubleLen(ET), sign,
            4-doubleLen(ROR), ROR);
    sprintf(tempStatsScreenBuffer[1], "BT:%.0f%-*c  RINT:%ds",
            BT, 4-doubleLen(BT), sign,
            RINT);
    lcd->setCursor(0, 0);
    lcd->print(tempStatsScreenBuffer[0]);
    lcd->setCursor(0, 1);
    lcd->print(tempStatsScreenBuffer[1]);
}

void i2cScreen::outputScreen(void) {
    //  =================
    // |FAN:100%  FIN   W|
    // |SP:350C   D:10:30|
    //  =================
    div_t time = div(roastDuration, 60);
    const char sign = isCelsius ? 'C':'F';
    const char *stateStr = roastStatesStr(roastStatus);
    sprintf(outputScreenBuffer[0], "FAN:%d%-*c%-*s",
            fanDutyCycle, 5-doubleLen(fanDutyCycle), '%',
            11 - strlen(stateStr), stateStr);
    sprintf(outputScreenBuffer[1], "SP:%.0f%-*cD:%02d:%02d",
            SP, 6-doubleLen(SP), sign,
            time.quot, time.rem);
    lcd->setCursor(0, 0);
    lcd->print(outputScreenBuffer[0]);
    lcd->setCursor(15, 0);
    lcd->write(wifiEnabled ? 1 : 0);
    lcd->setCursor(0, 1);
    lcd->print(outputScreenBuffer[1]);
}

void i2cScreen::doRefresh(void) {
    bool isInterval = roastDuration/3 & 1;
    if (roastStatus != STOPPED && isInterval) {
        tempStatsScreen();
    } else {
        outputScreen();
    }
}
