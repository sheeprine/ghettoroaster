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
        void setRefreshInterval(unsigned int interval);
        Roaster *getRoasterState(void);
        void tick(void);
};

#endif
