#include "roaster.h"


Roaster::Roaster() {
    ET = 0;
    BT = 0;
    ROR = 0;
    RORInterval = DEFAULT_ROR_INTERVAL;
}

Roaster::Roaster(unsigned int rorInterval) {
    Roaster();
    RORInterval = rorInterval;
}

void Roaster::startRoast() {
    roastStart = millis();
    nextROR = roastStart + RORInterval;
}

void Roaster::stopRoast() {
    roastStart = millis();
    nextROR = roastStart + RORInterval;
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
    updateROR();
}

unsigned long Roaster::getRoastTime() {
    return (millis() - roastStart) / 1000;
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
