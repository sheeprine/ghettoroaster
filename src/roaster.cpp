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

#include "roaster.h"

Roaster::Roaster() : m_kP(10), m_kI(0.4), m_kD(15) {
    mp_RORSource = &m_BT;
    mp_RORCalculator = new RORCalculator(DEFAULT_ROR_SAMPLING/1000);
    initPID();
}

Roaster::Roaster(unsigned int RORInterval) : Roaster() {
    m_RORInterval = RORInterval;
}

Roaster::~Roaster() {
    delete mp_pid;
    delete mp_RORCalculator;
}

void Roaster::initPID() {
    if (mp_pid) {
        delete mp_pid;
        mp_pid = nullptr;
    }
    mp_pid = new GhettoPID(m_kP, m_kI, m_kD);
}

void Roaster::setPIDTunings(double kp, double ki, double kd, int mode) {
    mp_pid->setTunings(kp, ki, kd, mode);
}

void Roaster::setPIDThreshold(unsigned int threshold) {
    mp_pid->setThreshold(threshold);
}

void Roaster::startPIDAutotune() {
    mp_pid->startAutotune();
}

void Roaster::stopPIDAutotune() {
    mp_pid->cancelAutotune();
}

void Roaster::startRoast() {
    m_roastStart = millis();
    m_nextROR = m_roastStart + m_RORSampling;
    mp_pid->enable();
}

void Roaster::stopRoast() {
    mp_pid->disable();
    m_roastStart = 0;
    m_nextROR = 0;
    mp_RORCalculator->reset();
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
    return mp_pid->getSetPoint();
}

void Roaster::setSP(double newSP) {
    mp_pid->setSetPoint(newSP);
}

double Roaster::getSV() {
    return mp_pid->getOutput();
}

void Roaster::setRoastingMinFanValue(unsigned int value) {
    m_enforceFanWithHeater = value;
}

unsigned int Roaster::getFan() {
    if (m_autoFan) {
        if (m_BT < 160) {
            m_fanDutyCycle = 100;
        }
        else if (m_BT < 180) {
            m_fanDutyCycle = 80;
        }
        else if (m_BT < 200) {
            m_fanDutyCycle = 70;
        }
        else {
            m_fanDutyCycle = 60;
        }
    }
    if (isHeaterEnabled() && (m_fanDutyCycle < m_enforceFanWithHeater))
        return m_enforceFanWithHeater;
    return m_fanDutyCycle;
}

void Roaster::setFan(unsigned int newFan) {
    m_fanDutyCycle = newFan > 100 ? 100 : newFan;
}

void Roaster::setAutoFanState(bool state) {
    m_autoFan = state;
}

bool Roaster::isHeaterEnabled() {
    return mp_pid->isOutputActivated();
}

unsigned long Roaster::getRoastTime() {
    if (m_roastStart)
        return (millis() - m_roastStart) / 1000;
    return 0;
}

void Roaster::updateROR() {
    if (m_nextROR <= millis()) {
        mp_RORCalculator->update(*mp_RORSource);
        m_nextROR = millis() + m_RORSampling;
    }
}

double Roaster::getROR() {
    if (m_RORInterval != DEFAULT_ROR_SAMPLING)
        return mp_RORCalculator->get(m_RORInterval/1000);
    return mp_RORCalculator->get();
}

double Roaster::getROR(unsigned int interval) {
    return mp_RORCalculator->get(interval);
}

unsigned int Roaster::getRORInterval() {
    return m_RORInterval / 1000;
}

void Roaster::setRORSource(RoastParams sourceType) {
    switch (sourceType) {
        case ET:
            mp_RORSource = &m_ET;
            break;
        default:
            mp_RORSource = &m_BT;
    }
    mp_RORCalculator->reset();
}

void Roaster::update() {
    mp_pid->setInput(m_BT);
    mp_pid->update();
    updateROR();
}
