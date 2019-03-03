#ifndef ROASTER_H
#define ROASTER_H

#include <Arduino.h>

#define DEFAULT_ROR_INTERVAL 30000;

enum roastParams {
    BT = 0,
    ET,
    SP,
    SV,
    ROR,
};

class Roaster {
    private:
        unsigned int RORInterval = DEFAULT_ROR_INTERVAL;
        unsigned int fanDutyCycle = 0;
        unsigned long roastStart, nextROR = 0;
        double ET, BT, SP, ROR, ROR_BT = 0;
        double *RORSource;
        // Conservative setting to avoid fire hazards
        unsigned short enforceFanWithHeater = 100;
        void updateROR();
    public:
        Roaster();
        Roaster(unsigned int rorInterval);
        void startRoast();
        void stopRoast();
        bool isRoasting();
        double getET();
        void setET(double newET);
        double getBT();
        void setBT(double newBT);
        double getSP();
        void setSP(double newSP);
        unsigned int getFan();
        void setRoastingMinFanValue(unsigned int value);
        void setFan(unsigned int newFan);
        bool isHeaterEnabled();
        unsigned long getRoastTime();
        void setRORSource(roastParams sourceType);
        double getROR();
        unsigned int getRORInterval();
        void update(void);
};

#endif
