#ifndef ROASTER_H
#define ROASTER_H

#include <Arduino.h>

#define DEFAULT_ROR_INTERVAL 30000;


class Roaster {
    private:
        unsigned int RORInterval = DEFAULT_ROR_INTERVAL;
        unsigned long roastStart, nextROR = 0;
        double ET, BT, SP, ROR, ROR_BT = 0;
        void updateROR();
    public:
        Roaster() {};
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
        unsigned long getRoastTime();
        double getROR();
        unsigned int getRORInterval();
};

#endif
