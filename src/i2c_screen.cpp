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

#ifdef I2C_SPEED_HACK
void i2cScreen::selectiveUpdate(unsigned short row, const char *next) {
    const char *rowBuffer = m_screenBuffer[row];
    for (unsigned short i=0; i<17; ++i) {
        if (rowBuffer[i] != next[i]) {
            mp_lcd->setCursor(i, row);
            mp_lcd->print(next[i]);
        }
    }
}
#endif

void i2cScreen::tempStatsScreen_alt() {
    //  =================
    // |ET:300C  R05:30.1|
    // |BT:300C  R30:18.4|
    //  =================
    const char sign = m_isCelsius ? 'C':'F';
    snprintf(m_tempStatsScreenBuffer[0], sizeof(m_tempStatsScreenBuffer[0]),
            "ET:%.0f%-*c  R05:%-*.1f",
            m_ET, 4-doubleLen(m_ET), sign,
            4-doubleLen(m_ROR5), m_ROR5);
    snprintf(m_tempStatsScreenBuffer[1], sizeof(m_tempStatsScreenBuffer[1]),
            "BT:%.0f%-*c  R30:%-*.1f",
            m_BT, 4-doubleLen(m_BT), sign,
            4-doubleLen(m_ROR30), m_ROR30);
}

void i2cScreen::tempStatsScreen() {
    //  =================
    // |ET:300C  ROR:30.1|
    // |BT:300C  RINT:60s|
    //  =================
    if (m_RINT) {
        const char sign = m_isCelsius ? 'C':'F';
        snprintf(m_tempStatsScreenBuffer[0], sizeof(m_tempStatsScreenBuffer[0]),
                "ET:%.0f%-*c  ROR:%-*.1f",
                m_ET, 4-doubleLen(m_ET), sign,
                4-doubleLen(m_ROR), m_ROR);
        snprintf(m_tempStatsScreenBuffer[1], sizeof(m_tempStatsScreenBuffer[1]),
                "BT:%.0f%-*c  RINT:%ds",
                m_BT, 4-doubleLen(m_BT), sign,
                m_RINT);
    }
    else {
        tempStatsScreen_alt();
    }
#ifndef I2C_SPEED_HACK
    mp_lcd->setCursor(0, 0);
    mp_lcd->print(m_tempStatsScreenBuffer[0]);
    mp_lcd->setCursor(0, 1);
    mp_lcd->print(m_tempStatsScreenBuffer[1]);
#else
    selectiveUpdate(0, m_tempStatsScreenBuffer[0]);
    selectiveUpdate(1, m_tempStatsScreenBuffer[1]);
    memcpy(m_screenBuffer[0], m_tempStatsScreenBuffer[0], 17);
    memcpy(m_screenBuffer[1], m_tempStatsScreenBuffer[1], 17);
#endif
}

void i2cScreen::outputScreen() {
    //  =================
    // |FAN:100%  FIN   W|
    // |SP:350C   D:10:30|
    //  =================
    div_t time = div(m_roastDuration, 60);
    const char sign = m_isCelsius ? 'C':'F';
    const char *stateStr = roastStatesStr(m_roastStatus);
    snprintf(m_outputScreenBuffer[0], sizeof(m_outputScreenBuffer[0]),
            "FAN:%d%-*c%-*s",
            m_fanDutyCycle, 5-doubleLen(m_fanDutyCycle), '%',
            11 - static_cast<int>(strlen(stateStr)), stateStr);
    snprintf(m_outputScreenBuffer[1], sizeof(m_outputScreenBuffer[1]),
            "SP:%.0f%-*cD:%02d:%02d",
            m_SP, 6-doubleLen(m_SP), sign,
            time.quot, time.rem);
#ifndef I2C_SPEED_HACK
    mp_lcd->setCursor(0, 0);
    mp_lcd->print(m_outputScreenBuffer[0]);
#else
    selectiveUpdate(0, m_outputScreenBuffer[0]);
#endif
    mp_lcd->setCursor(15, 0);
    mp_lcd->write(m_wifiEnabled ? 1 : 0);
#ifndef I2C_SPEED_HACK
    mp_lcd->setCursor(0, 1);
    mp_lcd->print(m_outputScreenBuffer[1]);
#else
    selectiveUpdate(1, m_outputScreenBuffer[1]);
    memcpy(m_screenBuffer[0], m_outputScreenBuffer[0], 17);
    memcpy(m_screenBuffer[1], m_outputScreenBuffer[1], 17);
#endif
}

void i2cScreen::doRefresh() {
    bool m_isInterval = m_roastDuration/3 & 1;
    if (m_roastStatus != STOPPED && m_isInterval) {
        tempStatsScreen();
    } else {
        outputScreen();
    }
}
