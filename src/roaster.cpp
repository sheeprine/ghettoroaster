#include "roaster.h"


Roaster::Roaster(void) : kp(75), ki(25), kd(50) {
    RORSource = &BT;
    initPID();
}

Roaster::Roaster(unsigned int rorInterval) : Roaster() {
    RORInterval = rorInterval;
}

Roaster::~Roaster(void) {
    delete pid;
}

void Roaster::initPID() {
    pid = new PID(&BT, &SV, &SP, kp, ki, kd, DIRECT);
}

void Roaster::startRoast() {
    roastStart = millis();
    nextROR = roastStart + RORInterval;
    pid->SetMode(AUTOMATIC);
}

void Roaster::stopRoast() {
    pid->SetMode(MANUAL);
    SV = 0;
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
    // FIXME(sheeprine): Using a threshold on the PID output as PWM is
    // inefficient on Zero Cross SSR. We should implement something more robust
    // and customizable.
    return SV > 150;
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
    pid->Compute();
}
