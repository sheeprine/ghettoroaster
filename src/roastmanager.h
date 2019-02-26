#ifndef ROASTMANAGER_H
#define ROASTMANAGER_H

#include <cstddef>
#include "roaster.h"
#include "screen.h"


class RoastManager {
    private:
        Roaster roastState;
        Screen *p_screen = NULL;
        bool autoCool = true;
        double(*p_envTemp)(void) = NULL;
        double(*p_beanTemp)(void) = NULL;
        double(*p_setpointTemp)(void) = NULL;
        unsigned int(*p_fanDuty)(void) = NULL;
        void(*p_fanSetDuty)(unsigned int) = NULL;
        bool(*p_roastEnabled)(void) = NULL;
        void updateRoastState(void);
        void refreshScreen(void);
    public:
        RoastManager() {};
        void addEnvTempFunc(double(*func)(void));
        void addBeanTempFunc(double(*func)(void));
        void addSetpointTempFunc(double(*func)(void));
        void addFanDutyFunc(unsigned int(*func)(void));
        void addFanSetDutyFunc(void(*func)(unsigned int));
        void addRoastEnabledFunc(bool(*func)(void));
        void addScreen(Screen *screen);
        void tick(void);
};

#endif
