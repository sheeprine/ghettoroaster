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

#ifndef SCREEN_H
#define SCREEN_H

enum roastStates {
    STOPPED = 0,
    DRY,
    TP,
    FC,
    FCE,
    SC,
    DROP,
    MAILL,
    FIN,
};

class Screen {
    private:
        virtual void doRefresh() = 0;
    protected:
        bool m_wifiEnabled = false;
        bool m_isCelsius = true;
        double m_ET, m_BT, m_SP, m_ROR5, m_ROR30, m_ROR = 0;
        unsigned int m_fanDutyCycle, m_RINT = 0;
        unsigned long m_roastDuration = 0;
        roastStates m_roastStatus = STOPPED;
        const char* roastStatesStr(roastStates state);
    public:
        virtual ~Screen() {};
        void setRoastStatus(roastStates status);
        void useCelsius();
        void useFarhenheit();
        void setWIFIStatus(bool enabled);
        void setET(double temp);
        void setBT(double temp);
        void setSP(double temp);
        void setFan(unsigned int dutyCycle);
        void setROR(double ror);
        void setROR5(double ror);
        void setROR30(double ror);
        void setRINT(unsigned int rorInterval);
        void setDuration(unsigned long duration);
        void refresh();
};

#endif
