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

void RoastManager::updateRoastState(void) {
    bool roastWantedState = p_roastEnabled();
    if (roastState.isRoasting() != roastWantedState) {
        if (roastWantedState) {
            roastState.startRoast();
        } else {
            roastState.stopRoast();
            if (autoCool) {
                // TODO(sheeprine): Set FAN to MAX to lower temp as a security
                // measure.
            }
        }
    }
}

void RoastManager::refreshScreen(void) {
    p_screen->setET(roastState.getET());
    p_screen->setBT(roastState.getBT());
    p_screen->setSP(roastState.getSP());
    p_screen->setFan(roastState.getFan());
    p_screen->setROR(roastState.getROR());
    p_screen->setRINT(roastState.getRORInterval());
    p_screen->setDuration(roastState.getRoastTime());
    p_screen->refresh();
}

void RoastManager::tick(void) {
    if (p_envTemp) {
        roastState.setET(p_envTemp());
    }
    if (p_beanTemp) {
        roastState.setBT(p_beanTemp());
    }
    if (p_setpointTemp) {
        roastState.setSP(p_setpointTemp());
    }
    updateRoastState();
    if (p_fanDuty) {
        roastState.setFan(p_fanDuty());
    }
    if (p_heaterEnabled) {
        p_heaterEnabled(roastState.isHeaterEnabled());
    }
    if (p_screen) {
        refreshScreen();
    }
}
