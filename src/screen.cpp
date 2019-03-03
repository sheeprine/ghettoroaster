#include "screen.h"


const char* Screen::roastStatesStr(roastStates state) {
    switch(roastStatus) {
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
    roastStatus = status;
}

void Screen::useCelsius(void) {
    isCelsius = true;
}

void Screen::useFarhenheit(void) {
    isCelsius = false;
}

void Screen::setWIFIStatus(bool enabled) {
    wifiEnabled = enabled;
}

void Screen::setET(double temp) {
    ET = temp;
}

void Screen::setBT(double temp) {
    BT = temp;
}

void Screen::setSP(double temp) {
    SP = temp;
}

void Screen::setFan(unsigned int dutyCycle) {
    fanDutyCycle = dutyCycle;
}

void Screen::setROR(double ror) {
    ROR = ror;
}

void Screen::setRINT(unsigned int rorInterval) {
    RINT = rorInterval;
}

void Screen::setDuration(unsigned long duration) {
    roastDuration = duration;
}

void Screen::refresh(void) {
    doRefresh();
}
