#include "roaster.h"


Roaster::Roaster(void) : m_kP(75), m_kI(25), m_kD(50) {
    mp_RORSource = &m_BT;
    initPID();
}

Roaster::Roaster(unsigned int rorInterval) : Roaster() {
    m_RORInterval = rorInterval;
}

Roaster::~Roaster(void) {
    delete mp_pid;
}

void Roaster::initPID() {
    mp_pid = new PID(&m_BT, &m_SV, &m_SP, m_kP, m_kI, m_kD, DIRECT);
}

void Roaster::startRoast() {
    m_roastStart = millis();
    m_nextROR = m_roastStart + m_RORInterval;
    mp_pid->SetMode(AUTOMATIC);
}

void Roaster::stopRoast() {
    mp_pid->SetMode(MANUAL);
    m_SV = 0;
    m_roastStart = 0;
    m_nextROR = 0;
}

bool Roaster::isRoasting() {
    return m_roastStart > 0;
}

double Roaster::getET() {
    return m_ET;
}

void Roaster::setET(double newET) {
    m_ET = newET;
}

double Roaster::getBT() {
    return m_BT;
}

void Roaster::setBT(double newBT) {
    m_BT = newBT;
}

double Roaster::getSP() {
    return m_SP;
}

void Roaster::setSP(double newSP) {
    m_SP = newSP;
}

void Roaster::setRoastingMinFanValue(unsigned int value) {
    m_enforceFanWithHeater = value;
}

unsigned int Roaster::getFan() {
    if (isHeaterEnabled() && (m_fanDutyCycle < m_enforceFanWithHeater))
        return m_enforceFanWithHeater;
    return m_fanDutyCycle;
}

void Roaster::setFan(unsigned int newFan) {
    m_fanDutyCycle = newFan > 100 ? 100 : newFan;
}

bool Roaster::isHeaterEnabled() {
    // FIXME(sheeprine): Using a threshold on the PID output as PWM is
    // inefficient on Zero Cross SSR. We should implement something more robust
    // and customizable.
    return m_SV > 150;
}

unsigned long Roaster::getRoastTime() {
    if (m_roastStart)
        return (millis() - m_roastStart) / 1000;
    return 0;
}

void Roaster::updateROR() {
    if (m_nextROR <= millis()) {
        m_ROR = m_BT - m_ROR_BT;
        m_ROR_BT = m_BT;
        m_nextROR = millis() + m_RORInterval;
    }
}

double Roaster::getROR() {
    return m_ROR;
}

unsigned int Roaster::getRORInterval() {
    return m_RORInterval / 1000;
}

void Roaster::setRORSource(roastParams sourceType) {
    mp_RORSource = &m_BT;
    switch(sourceType) {
        case ET:
            mp_RORSource = &m_ET;
            break;
        case SP:
            mp_RORSource = &m_SP;
            break;
        case SV:
            mp_RORSource = &m_SV;
            break;
        default:
            mp_RORSource = &m_BT;
    }
}

void Roaster::update() {
    updateROR();
    mp_pid->Compute();
}
