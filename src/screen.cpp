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

#include "screen.h"


const char* Screen::roastStatesStr(roastStates state) {
    switch (state) {
        case DRY:
            return "DRY";
        case TP:
        case MAILL:
            return "MAILL";
        case FC:
        case FCE:
        case SC:
        case FIN:
            return "FIN";
        case DROP:
            return "DROP";
        default:
            return "STOP";
    }
}

void Screen::setRoastStatus(roastStates status) {
    m_roastStatus = status;
}

void Screen::useCelsius() {
    m_isCelsius = true;
}

void Screen::useFarhenheit() {
    m_isCelsius = false;
}

void Screen::setWIFIStatus(bool enabled) {
    m_wifiEnabled = enabled;
}

void Screen::setET(double temp) {
    m_ET = temp;
}

void Screen::setBT(double temp) {
    m_BT = temp;
}

void Screen::setSP(double temp) {
    m_SP = temp;
}

void Screen::setFan(unsigned int dutyCycle) {
    m_fanDutyCycle = dutyCycle;
}

void Screen::setROR(double ror) {
    m_ROR = ror;
}

void Screen::setROR5(double ror) {
    m_ROR5 = ror;
}

void Screen::setROR30(double ror) {
    m_ROR30 = ror;
}

void Screen::setRINT(unsigned int rorInterval) {
    m_RINT = rorInterval;
}

void Screen::setDuration(unsigned long duration) {
    m_roastDuration = duration;
}

void Screen::refresh() {
    doRefresh();
}
