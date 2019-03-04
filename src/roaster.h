#ifndef ROASTER_H
#define ROASTER_H

#include <Arduino.h>
#include <PID_v1.h>

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
        PID *mp_pid = NULL;
        unsigned int m_RORInterval = DEFAULT_ROR_INTERVAL;
        unsigned int m_fanDutyCycle = 0;
        unsigned long m_roastStart, m_nextROR = 0;
        double *mp_RORSource;
        double m_ET, m_BT, m_SP, m_SV, m_ROR, m_ROR_BT = 0;
        double m_kP, m_kI, m_kD;
        // Conservative setting to avoid fire hazards
        unsigned short m_enforceFanWithHeater = 100;
        void updateROR();
    public:
        Roaster();
        Roaster(unsigned int rorInterval);
        ~Roaster(void);
        void initPID(void);
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
