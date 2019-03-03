#include "roaster.h"


Roaster::Roaster(void) {
    RORSource = &BT;
}

Roaster::Roaster(unsigned int rorInterval) : Roaster() {
    RORInterval = rorInterval;
}

void Roaster::startRoast() {
    roastStart = millis();
    nextROR = roastStart + RORInterval;
}

void Roaster::stopRoast() {
    roastStart = 0;
    nextROR = 0;
}

bool Roaster::isRoasting() {
    return roastStart > 0;
}

double Roaster::getET() {
    return ET;
}

void Roaster::setET(double newET) {
    ET = newET;
}

double Roaster::getBT() {
    return BT;
}

void Roaster::setBT(double newBT) {
    BT = newBT;
}

double Roaster::getSP() {
    return SP;
}

void Roaster::setSP(double newSP) {
    SP = newSP;
}

void Roaster::setRoastingMinFanValue(unsigned int value) {
    enforceFanWithHeater = value;
}

unsigned int Roaster::getFan() {
    if (isHeaterEnabled() && (fanDutyCycle < enforceFanWithHeater))
        return enforceFanWithHeater;
    return fanDutyCycle;
}

void Roaster::setFan(unsigned int newFan) {
    fanDutyCycle = newFan > 100 ? 100 : newFan;
}

bool Roaster::isHeaterEnabled() {
    //TODO(sheeprine): Placeholder for PID control, keeping it off for security
    //reasons.
    return false;
}

unsigned long Roaster::getRoastTime() {
    if (roastStart)
        return (millis() - roastStart) / 1000;
    return 0;
}

void Roaster::updateROR() {
    if (nextROR <= millis()) {
        ROR = BT - ROR_BT;
        ROR_BT = BT;
        nextROR = millis() + RORInterval;
    }
}

double Roaster::getROR() {
    return ROR;
}

unsigned int Roaster::getRORInterval() {
    return RORInterval / 1000;
}

void Roaster::setRORSource(roastParams sourceType) {
    RORSource = &BT;
}

void Roaster::update() {
    updateROR();
}
