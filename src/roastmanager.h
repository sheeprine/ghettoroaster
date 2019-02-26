#ifndef ROASTMANAGER_H
#define ROASTMANAGER_H

#include <cstddef>
#include "roaster.h"
#include "screen.h"


class RoastManager {
    private:
        Roaster roasterState;
        Screen *p_screen = NULL;
        bool autoCool = true;
        double(*p_envTemp)(void) = NULL;
        double(*p_beanTemp)(void) = NULL;
        double(*p_setpointTemp)(void) = NULL;
        unsigned int(*p_fanDuty)(void) = NULL;
        void(*p_fanSetDuty)(unsigned int) = NULL;
        void(*p_heaterEnabled)(bool) = NULL;
        bool(*p_roastEnabled)(void) = NULL;
        void updateRoasterState(void);
        void refreshScreen(void);
    public:
        RoastManager() {};
        void addEnvTempFunc(double(*func)(void));
        void addBeanTempFunc(double(*func)(void));
        void addSetpointTempFunc(double(*func)(void));
        void addFanDutyFunc(unsigned int(*func)(void));
        void addFanSetDutyFunc(void(*func)(unsigned int));
        void addHeaterEnabledFunc(void(*func)(bool));
        void addRoastEnabledFunc(bool(*func)(void));
        void addScreen(Screen *screen);
        Roaster *getRoasterState(void);
        void tick(void);
};

#endif
