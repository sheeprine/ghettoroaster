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
        double m_ET, m_BT, m_SP, m_ROR = 0;
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
        void setRINT(unsigned int rorInterval);
        void setDuration(unsigned long duration);
        void refresh();
};

#endif
