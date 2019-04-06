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

#include "roastmanager.h"


void RoastManager::addEnvTempFunc(double(*func)()) {
    p_envTemp = func;
}

void RoastManager::addBeanTempFunc(double(*func)()) {
    p_beanTemp = func;
}

void RoastManager::addSetpointTempFunc(double(*func)()) {
    p_setpointTemp = func;
}

void RoastManager::addFanDutyFunc(unsigned int(*func)()) {
    p_fanDuty = func;
}

void RoastManager::addSetFanDutyFunc(void(*func)(unsigned int)) {
    p_setFanDuty = func;
}

void RoastManager::addSetAutoFanState(void (*func)(bool)) {
    p_setAutoFan = func;
}

void RoastManager::addHeaterEnabledFunc(void(*func)(bool)) {
    p_heaterEnabled = func;
}

void RoastManager::addHeaterPWMFunc(void(*func)(unsigned int)) {
    p_heaterPWM = func;
}

void RoastManager::addRoastEnabledFunc(bool(*func)()) {
    p_roastEnabled = func;
}

void RoastManager::addScreen(Screen *screen) {
    mp_screen = screen;
}

Roaster *RoastManager::getRoasterState() {
    // FIXME(sheeprine): We shouldn't expose internal roaster state. But for
    // the moment it's convenient.
    return &m_roasterState;
}

void RoastManager::setRefreshInterval(unsigned int interval) {
    m_refreshInterval = interval;
}

void RoastManager::updateRoasterState() {
    bool roastWantedState = false;
    if (p_roastEnabled)
        roastWantedState = p_roastEnabled();
    if (m_roasterState.isRoasting() != roastWantedState) {
        if (roastWantedState) {
            m_roasterState.startRoast();
        } else {
            m_roasterState.stopRoast();
            if (m_autoFan)
                m_roasterState->setFan(m_autoCoolValue);
        }
    }
}

void RoastManager::refreshScreen() {
    mp_screen->setET(m_roasterState.getET());
    mp_screen->setBT(m_roasterState.getBT());
    mp_screen->setSP(m_roasterState.getSP());
    mp_screen->setFan(m_roasterState.getFan());
    mp_screen->setROR(m_roasterState.getROR());
    if (m_useDetailedROR) {
        mp_screen->setROR5(m_roasterState.getROR(5));
        mp_screen->setROR30(m_roasterState.getROR(30));
    }
    else {
        mp_screen->setRINT(m_roasterState.getRORInterval());
    }
    mp_screen->setDuration(m_roasterState.getRoastTime());
    mp_screen->setRoastStatus(roastStates(m_roasterState.isRoasting()));
    mp_screen->refresh();
}

void RoastManager::tick() {
    if (millis() - m_lastRefresh > m_refreshInterval) {
        if (p_envTemp) {
            m_roasterState.setET(p_envTemp());
        }
        if (p_beanTemp) {
            m_roasterState.setBT(p_beanTemp());
        }
        m_lastRefresh = millis();
    }
    if (p_setpointTemp) {
        m_roasterState.setSP(p_setpointTemp());
    }
    updateRoasterState();
    if (p_setAutoFan) {
        m_roasterState.m_autoFan = p_setAutoFan();
    }
    if (p_fanDuty and !m_autoFan) {
        m_roasterState.setFan(p_fanDuty());
    }
    if (p_setFanDuty) {
        p_setFanDuty(m_roasterState.getFan());
    }
    if (p_heaterEnabled) {
        p_heaterEnabled(m_roasterState.isHeaterEnabled());
    }
    if (p_heaterPWM) {
        p_heaterPWM(m_roasterState.getSV());
    }
    if (mp_screen) {
        refreshScreen();
    }
    m_roasterState.update();
}
