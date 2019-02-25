#include "roastmanager.h"


void RoastManager::addEnvTempFunc(double(*func)(void)) {
    p_envTemp = func;
}

void RoastManager::addBeanTempFunc(double(*func)(void)) {
    p_beanTemp = func;
}

void RoastManager::addRoastEnabledFunc(bool(*func)(void)) {
    p_roastEnabled = func;
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

void RoastManager::tick(void) {
    if (p_envTemp) {
        roastState.setET(p_envTemp());
    }
    if (p_beanTemp) {
        roastState.setBT(p_beanTemp());
    }
    updateRoastState();
}
