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
    p_screen = screen;
}

Roaster *RoastManager::getRoasterState(void) {
    // FIXME(sheeprine): We shouldn't expose internal roaster state. But for
    // the moment it's convenient.
    return &roasterState;
}

void RoastManager::updateRoasterState(void) {
    bool roastWantedState = p_roastEnabled();
    if (roasterState.isRoasting() != roastWantedState) {
        if (roastWantedState) {
            roasterState.startRoast();
        } else {
            roasterState.stopRoast();
            if (autoCool) {
                // TODO(sheeprine): Set FAN to MAX to lower temp as a security
                // measure.
            }
        }
    }
}

void RoastManager::refreshScreen(void) {
    p_screen->setET(roasterState.getET());
    p_screen->setBT(roasterState.getBT());
    p_screen->setSP(roasterState.getSP());
    p_screen->setFan(roasterState.getFan());
    p_screen->setROR(roasterState.getROR());
    p_screen->setRINT(roasterState.getRORInterval());
    p_screen->setDuration(roasterState.getRoastTime());
    p_screen->setRoastStatus(roastStates(roasterState.isRoasting()));
    p_screen->refresh();
}

void RoastManager::tick(void) {
    if (p_envTemp) {
        roasterState.setET(p_envTemp());
    }
    if (p_beanTemp) {
        roasterState.setBT(p_beanTemp());
    }
    if (p_setpointTemp) {
        roasterState.setSP(p_setpointTemp());
    }
    updateRoasterState();
    if (p_fanDuty) {
        roasterState.setFan(p_fanDuty());
    }
    if (p_heaterEnabled) {
        p_heaterEnabled(roasterState.isHeaterEnabled());
    }
    if (p_screen) {
        refreshScreen();
    }
}
