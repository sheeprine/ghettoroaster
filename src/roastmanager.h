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
        Screen *mp_screen = nullptr;
        bool m_autoCool = true;
        double(*p_envTemp)() = nullptr;
        double(*p_beanTemp)() = nullptr;
        double(*p_setpointTemp)() = nullptr;
        unsigned int(*p_fanDuty)() = nullptr;
        void(*p_fanSetDuty)(unsigned int) = nullptr;
        void(*p_heaterEnabled)(bool) = nullptr;
        bool(*p_roastEnabled)() = nullptr;
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
