#ifndef ROASTMANAGER_H
#define ROASTMANAGER_H

#include <cstddef>
#include "roaster.h"
#include "screen.h"


class RoastManager {
    private:
        unsigned int m_refreshInterval = 500;
        unsigned long m_lastRefresh = 0;
        Roaster m_roasterState;
        Screen *mp_screen = NULL;
        bool m_autoCool = true;
        double(*p_envTemp)() = NULL;
        double(*p_beanTemp)() = NULL;
        double(*p_setpointTemp)() = NULL;
        unsigned int(*p_fanDuty)() = NULL;
        void(*p_fanSetDuty)(unsigned int) = NULL;
        void(*p_heaterEnabled)(bool) = NULL;
        bool(*p_roastEnabled)() = NULL;
        void updateRoasterState();
        void refreshScreen();
    public:
        RoastManager() {};
        void addEnvTempFunc(double(*func)());
        void addBeanTempFunc(double(*func)());
        void addSetpointTempFunc(double(*func)());
        void addFanDutyFunc(unsigned int(*func)());
        void addFanSetDutyFunc(void(*func)(unsigned int));
        void addHeaterEnabledFunc(void(*func)(bool));
        void addRoastEnabledFunc(bool(*func)());
        void addScreen(Screen *screen);
        void setRefreshInterval(unsigned int interval);
        Roaster *getRoasterState();
        void tick();
};

#endif
