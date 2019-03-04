#include "roastmanager.h"


void RoastManager::addEnvTempFunc(double(*func)(void)) {
    p_envTemp = func;
}

void RoastManager::addBeanTempFunc(double(*func)(void)) {
    p_beanTemp = func;
}

void RoastManager::addSetpointTempFunc(double(*func)(void)) {
    p_setpointTemp = func;
}

void RoastManager::addFanDutyFunc(unsigned int(*func)(void)) {
    p_fanDuty = func;
}

void RoastManager::addFanSetDutyFunc(void(*func)(unsigned int)) {
    p_fanSetDuty = func;
}

void RoastManager::addHeaterEnabledFunc(void(*func)(bool)) {
    p_heaterEnabled = func;
}

void RoastManager::addRoastEnabledFunc(bool(*func)(void)) {
    p_roastEnabled = func;
}

void RoastManager::addScreen(Screen *screen) {
    mp_screen = screen;
}

Roaster *RoastManager::getRoasterState(void) {
    // FIXME(sheeprine): We shouldn't expose internal roaster state. But for
    // the moment it's convenient.
    return &m_roasterState;
}

void RoastManager::setRefreshInterval(unsigned int interval) {
    m_refreshInterval = interval;
}

void RoastManager::updateRoasterState(void) {
    bool roastWantedState = p_roastEnabled();
    if (m_roasterState.isRoasting() != roastWantedState) {
        if (roastWantedState) {
            m_roasterState.startRoast();
        } else {
            m_roasterState.stopRoast();
            if (m_autoCool) {
                // TODO(sheeprine): Set FAN to MAX to lower temp as a security
                // measure.
            }
        }
    }
}

void RoastManager::refreshScreen(void) {
    mp_screen->setET(m_roasterState.getET());
    mp_screen->setBT(m_roasterState.getBT());
    mp_screen->setSP(m_roasterState.getSP());
    mp_screen->setFan(m_roasterState.getFan());
    mp_screen->setROR(m_roasterState.getROR());
    mp_screen->setRINT(m_roasterState.getRORInterval());
    mp_screen->setDuration(m_roasterState.getRoastTime());
    mp_screen->setRoastStatus(roastStates(m_roasterState.isRoasting()));
    mp_screen->refresh();
}

void RoastManager::tick(void) {
    if (millis() - m_lastRefresh > m_refreshInterval) {
        if (p_envTemp) {
            m_roasterState.setET(p_envTemp());
        }
        if (p_beanTemp) {
            m_roasterState.setBT(p_beanTemp());
        }
        if (p_setpointTemp) {
            m_roasterState.setSP(p_setpointTemp());
        }
        m_lastRefresh = millis();
    }
    updateRoasterState();
    if (p_fanDuty) {
        m_roasterState.setFan(p_fanDuty());
    }
    if (p_heaterEnabled) {
        p_heaterEnabled(m_roasterState.isHeaterEnabled());
    }
    if (mp_screen) {
        refreshScreen();
    }
    m_roasterState.update();
}
