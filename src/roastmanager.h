#ifndef ROASTMANAGER_H
#define ROASTMANAGER_H

#include <cstddef>
#include "roaster.h"


class RoastManager {
    private:
        Roaster roastState;
        bool autoCool = true;
        double(*p_envTemp)(void) = NULL;
        double(*p_beanTemp)(void) = NULL;
        bool(*p_roastEnabled)(void) = NULL;
        void updateRoastState(void);
    public:
        RoastManager() {};
        void addEnvTempFunc(double(*func)(void));
        void addBeanTempFunc(double(*func)(void));
        void addRoastEnabledFunc(bool(*func)(void));
        void tick(void);
};

#endif
