#ifndef ROASTER_H
#define ROASTER_H

#include <Arduino.h>

#define DEFAULT_ROR_INTERVAL 30000;


class Roaster {
    private:
        unsigned long roastStart;
        double ET, BT;
        double ROR, ROR_BT;
        unsigned int RORInterval;
        unsigned long nextROR;
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
        unsigned long getRoastTime();
        double getROR();
        unsigned int getRORInterval();
};

#endif
