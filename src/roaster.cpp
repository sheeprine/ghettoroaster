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
    mp_pid = new PID(&m_BT, &m_SV, &m_SP, m_kP, m_kI, m_kD, P_ON_E, DIRECT);
}

void Roaster::setPIDTunings(double kp, double ki, double kd, int mode) {
    mp_pid->SetTunings(kp, ki, kd, mode);
}

void Roaster::setPIDThreshold(unsigned int threshold) {
    m_pidActivationThreshold = threshold;
}

void Roaster::startPIDAutotune() {
    if (!mp_pidATune) {
        mp_pidATune = new PID_ATune(&m_BT, &m_SV);
        // NOTE(sheeprine): Tune for full P I D
        mp_pidATune->SetControlType(1);
        // NOTE(sheeprine): Increase SV by 10% steps
        mp_pidATune->SetOutputStep(25);
        mp_pidATune->SetLookbackSec(30);
        mp_pidATune->SetNoiseBand(1);
    }
}

void Roaster::refreshPIDAutotune() {
    if (mp_pidATune) {
        if (mp_pidATune->Runtime()) {
            Serial.println("PID AutoTune done.");
            Serial.print("Kp: ");
            Serial.println(mp_pidATune->GetKp());
            Serial.print("Ki: ");
            Serial.println(mp_pidATune->GetKi());
            Serial.print("Kd: ");
            Serial.println(mp_pidATune->GetKd());
            mp_pid->SetTunings(
                mp_pidATune->GetKp(),
                mp_pidATune->GetKi(),
                mp_pidATune->GetKd());
            stopPIDAutotune();
        }
    }
}

void Roaster::stopPIDAutotune() {
    if (mp_pidATune) {
        mp_pidATune->Cancel();
        delete mp_pidATune;
        mp_pidATune = nullptr;
    }
}

void Roaster::startRoast() {
    m_roastStart = millis();
    m_nextROR = m_roastStart + m_RORSampling;
    mp_pid->SetMode(AUTOMATIC);
}

void Roaster::stopRoast() {
    mp_pid->SetMode(MANUAL);
    m_SV = 0;
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
    return m_SP;
}

void Roaster::setSP(double newSP) {
    m_SP = newSP;
}

double Roaster::getSV() {
    return m_SV;
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
    // FIXME(sheeprine): Using a threshold on the PID output as PWM is
    // inefficient on Zero Cross SSR. We should implement something more robust
    // and customizable.
    return m_SV > m_pidActivationThreshold;
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
        case SP:
            mp_RORSource = &m_SP;
            break;
        case SV:
            mp_RORSource = &m_SV;
            break;
        default:
            mp_RORSource = &m_BT;
    }
    mp_RORCalculator->reset();
}

void Roaster::update() {
    if (mp_pidATune) {
        refreshPIDAutotune();
    }
    else {
        mp_pid->Compute();
    }
    updateROR();
}
