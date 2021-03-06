/*
Copyright 2019 Stephane Albert

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef ROASTER_H
#define ROASTER_H

#include <Arduino.h>
#include "pid.h"
#include "ror_calculator.h"

#define DEFAULT_ROR_SAMPLING 1000

enum RoastParams {
    BT = 0,
    ET,
    SP,
    SV,
    ROR,
};

class Roaster {
    private:
        GhettoPID *mp_pid = nullptr;
        RORCalculator *mp_RORCalculator = nullptr;
        unsigned int m_RORSampling = DEFAULT_ROR_SAMPLING;
        unsigned int m_RORInterval = DEFAULT_ROR_SAMPLING;
        unsigned int m_fanDutyCycle = 0;
        unsigned long m_roastStart, m_nextROR = 0;
        double *mp_RORSource;
        double m_ET, m_BT, m_kP, m_kI, m_kD = 0;
        bool m_autoFan = false;
        // Conservative setting to avoid fire hazards
        unsigned short m_enforceFanWithHeater = 10;
        void initPID();
        void updateROR();
    public:
        Roaster();
        Roaster(unsigned int RORInterval);
        ~Roaster();
        void setPIDTunings(double kp, double ki, double kd, int mode);
        void setPIDThreshold(unsigned int threshold);
        void startPIDAutotune();
        void stopPIDAutotune();
        void startRoast();
        void stopRoast();
        bool isRoasting();
        double getET();
        void setET(double newET);
        double getBT();
        void setBT(double newBT);
        double getSP();
        void setSP(double newSP);
        double getSV();
        void setRoastingMinFanValue(unsigned int value);
        void setFan(unsigned int newFan);
        unsigned int getFan();
        void setAutoFanState(bool state);
        bool isHeaterEnabled();
        unsigned long getRoastTime();
        void setRORSource(RoastParams sourceType);
        double getROR();
        double getROR(unsigned int interval);
        unsigned int getRORInterval();
        void update();
};

#endif
