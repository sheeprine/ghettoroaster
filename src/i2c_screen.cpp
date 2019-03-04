#include "i2c_screen.h"

i2cScreen::i2cScreen(LiquidCrystal_I2C *i2cLCD) {
    mp_lcd = i2cLCD;
    mp_lcd->init();
    mp_lcd->backlight();
    mp_lcd->createChar(0, noWIFI);
    mp_lcd->createChar(1, WIFI);
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
    const char sign = m_isCelsius ? 'C':'F';
    sprintf(m_tempStatsScreenBuffer[0], "ET:%.0f%-*c  ROR:%-*.1f",
            m_ET, 4-doubleLen(m_ET), sign,
            4-doubleLen(m_ROR), m_ROR);
    sprintf(m_tempStatsScreenBuffer[1], "BT:%.0f%-*c  RINT:%ds",
            m_BT, 4-doubleLen(m_BT), sign,
            m_RINT);
    mp_lcd->setCursor(0, 0);
    mp_lcd->print(m_tempStatsScreenBuffer[0]);
    mp_lcd->setCursor(0, 1);
    mp_lcd->print(m_tempStatsScreenBuffer[1]);
}

void i2cScreen::outputScreen(void) {
    //  =================
    // |FAN:100%  FIN   W|
    // |SP:350C   D:10:30|
    //  =================
    div_t time = div(m_roastDuration, 60);
    const char sign = m_isCelsius ? 'C':'F';
    const char *stateStr = roastStatesStr(m_roastStatus);
    sprintf(m_outputScreenBuffer[0], "FAN:%d%-*c%-*s",
            m_fanDutyCycle, 5-doubleLen(m_fanDutyCycle), '%',
            11 - strlen(stateStr), stateStr);
    sprintf(m_outputScreenBuffer[1], "SP:%.0f%-*cD:%02d:%02d",
            m_SP, 6-doubleLen(m_SP), sign,
            time.quot, time.rem);
    mp_lcd->setCursor(0, 0);
    mp_lcd->print(m_outputScreenBuffer[0]);
    mp_lcd->setCursor(15, 0);
    mp_lcd->write(m_wifiEnabled ? 1 : 0);
    mp_lcd->setCursor(0, 1);
    mp_lcd->print(m_outputScreenBuffer[1]);
}

void i2cScreen::doRefresh(void) {
    bool m_isInterval = m_roastDuration/3 & 1;
    if (m_roastStatus != STOPPED && m_isInterval) {
        tempStatsScreen();
    } else {
        outputScreen();
    }
}
